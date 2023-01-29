
// ScreenShotDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ScreenShot.h"
#include "ScreenShotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 鼠标钩子
HHOOK g_hHook = NULL;
LRESULT CALLBACK MouseProc(int nCode, WPARAM msg, LPARAM lparam)
{
	CWnd* pMainWnd = AfxGetApp()->GetMainWnd();
	if (pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CScreenShotDlg)))
	{
		if (WM_LBUTTONDOWN == msg)
		{
			PMOUSEHOOKSTRUCT mh = (PMOUSEHOOKSTRUCT)lparam;
			POINT pt;
			pt.x = mh->pt.x;	//此处的坐标均为屏幕坐标
			pt.y = mh->pt.y;
			pMainWnd->PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
			return 1;
		}
		else if (WM_MOUSEMOVE == msg)
		{
			PMOUSEHOOKSTRUCT mh = (PMOUSEHOOKSTRUCT)lparam;
			POINT pt;
			pt.x = mh->pt.x;
			pt.y = mh->pt.y;
			pMainWnd->PostMessage(WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
			//return 1;
		}
		else if (WM_LBUTTONUP == msg)
		{
			PMOUSEHOOKSTRUCT mh = (PMOUSEHOOKSTRUCT)lparam;
			POINT pt;
			pt.x = mh->pt.x;
			pt.y = mh->pt.y;
			pMainWnd->PostMessage(WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
			return 1;
		}
	}

	return CallNextHookEx(g_hHook, nCode, msg, lparam);
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CScreenShotDlg, CDialog)

CScreenShotDlg::CScreenShotDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCREENSHOT_DIALOG, pParent)
	,m_bDraging(false)
	,m_nScrolHPos(0)
	,m_nScrolVPos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_PREVIEW, m_wndPicPreview);
	DDX_Control(pDX, IDC_SCROLL_VERT, m_wndVertScroll);
	DDX_Control(pDX, IDC_SCROLL_HOR, m_wndHorScroll);
}

BEGIN_MESSAGE_MAP(CScreenShotDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCREEN_SHOT, &CScreenShotDlg::OnBnClickedBtnScreenShot)
	ON_WM_DRAWITEM()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

BOOL CScreenShotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	m_wndPicPreview.GetWindowRect(&rect);
	SCROLLINFO infoScrollHor = { sizeof(SCROLLINFO),SIF_ALL,
		0,0,rect.Width(),0,0 };
	m_wndHorScroll.SetScrollInfo(&infoScrollHor);

	SCROLLINFO infoScrollVert = { sizeof(SCROLLINFO),SIF_ALL,
	0,0,rect.Height(),0,0 };
	m_wndVertScroll.SetScrollInfo(&infoScrollVert);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScreenShotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CScreenShotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//反转一个矩形屏幕范围的像素
void InvertBlock(CWnd* pWndSrc, POINT ptBeg, POINT ptEnd)
{
	CDC* pDC = pWndSrc->GetDCEx(NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	pDC->PatBlt(ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y, DSTINVERT);
	pWndSrc->ReleaseDC(pDC);
}

void CScreenShotDlg::OnBnClickedBtnScreenShot()
{
	SetCapture();
	SetCursor(LoadCursor(NULL, IDC_CROSS));	
	g_hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);//注册钩子函数
	//隐藏对话框,这里不能隐藏对话框，否则会出错
	//ShowWindow(SW_HIDE);

	//锁定桌面窗口更新
	CWnd* pWndDeskTop = GetDesktopWindow();
	if (!pWndDeskTop && !pWndDeskTop->LockWindowUpdate())
		return;

	//开始消息循环
	MSG msg;
	POINT ptBegin, ptEnd;
	m_bDraging = false;
	bool bSkipLoop = false;
	while (GetMessage(&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST))
	{
		if (CWnd::GetCapture() != this)
			break;

		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
			m_bDraging = true;
			ptBegin = msg.pt;
			ptEnd = ptBegin;
			InvertBlock(pWndDeskTop, ptBegin, ptEnd);
			break;
		case WM_MOUSEMOVE:
			if (m_bDraging)
			{
				InvertBlock(pWndDeskTop, ptBegin, ptEnd);//先反转为正常的颜色
				ptEnd = msg.pt;
				InvertBlock(pWndDeskTop, ptBegin, ptEnd);
			}
			break;
		case WM_LBUTTONUP:
			if (m_bDraging)
			{
				InvertBlock(pWndDeskTop, ptBegin, ptEnd);
				ptEnd = msg.pt;
				//画出正确的矩形，保证起始点和终点的正确性
				if (m_bmpMemory.m_hObject)
					m_bmpMemory.DeleteObject();
				CDC* pDcPic = m_wndPicPreview.GetDC();
				m_bmpMemory.CreateCompatibleBitmap(pDcPic, abs(ptEnd.x - ptBegin.x), abs(ptEnd.y - ptBegin.y));
				CDC dcMemory;
				dcMemory.CreateCompatibleDC(pDcPic);
				ReleaseDC(pDcPic);

				CBitmap* pOldBmp = dcMemory.SelectObject(&m_bmpMemory);
				CDC *pDcScreen = pWndDeskTop->GetDCEx(NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
				dcMemory.BitBlt(0, 0, abs(ptEnd.x - ptBegin.x), abs(ptEnd.y - ptEnd.x),
					pDcScreen, ptBegin.x, ptBegin.y, SRCCOPY);
				dcMemory.SelectObject(pOldBmp);
				ReleaseDC(pDcScreen);

				//动态设置滚动条滑块的范围和Page
				CRect rect;
				m_wndPicPreview.GetWindowRect(&rect);
				SCROLLINFO infoVert = { sizeof(SCROLLINFO),SIF_ALL,	0,
					max(0, abs(ptEnd.y - ptBegin.y)),rect.Height(),0,0 };
				m_wndVertScroll.SetScrollInfo(&infoVert);

				SCROLLINFO infoHor = { sizeof(SCROLLINFO),SIF_ALL,	0,
					max(0, abs(ptEnd.x - ptBegin.x)),rect.Width(),0,0 };
				m_wndHorScroll.SetScrollInfo(&infoHor);

				bSkipLoop = true;
				m_bDraging = false;
			}
			break;
		default:
			break;
		}
		if (bSkipLoop)
			break;
	}

	if (g_hHook)
	{
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}

	ReleaseCapture();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	pWndDeskTop->UnlockWindowUpdate();
	m_wndPicPreview.Invalidate();
}


void CScreenShotDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (nIDCtl == IDC_PIC_PREVIEW)
	{
		if (m_bmpMemory.m_hObject)
		{
			CDC* pDcPic = m_wndPicPreview.GetDC();
			BITMAP infoBmp;
			m_bmpMemory.GetBitmap(&infoBmp);
			CDC dcMemory;
			dcMemory.CreateCompatibleDC(pDcPic);
			CBitmap* pOldBmp = dcMemory.SelectObject(&m_bmpMemory);

			CRect rect;
			m_wndPicPreview.GetWindowRect(&rect);			
			pDcPic->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);//首先，清空背景
			pDcPic->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory,
				m_nScrolHPos, m_nScrolVPos, SRCCOPY);
			dcMemory.SelectObject(pOldBmp);

			ReleaseDC(pDcPic);
		}
	}
}

void CScreenShotDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos);
	maxpos = pScrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	m_nScrolHPos = pScrollBar->GetScrollPos();

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		m_nScrolHPos = minpos;
		break;
	case SB_RIGHT:      // Scroll to far right.
		m_nScrolHPos = maxpos;
		break;
	case SB_ENDSCROLL:   // End scroll.
		break;
	case SB_LINELEFT:      // Scroll left.
		if (m_nScrolHPos > minpos)
			m_nScrolHPos--;
		break;
	case SB_LINERIGHT:   // Scroll right.
		if (m_nScrolHPos < maxpos)
			m_nScrolHPos++;
		break;
	case SB_PAGELEFT:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (m_nScrolHPos > minpos)
			m_nScrolHPos = max(minpos, m_nScrolHPos - (int)info.nPage);
	}
	break;
	case SB_PAGERIGHT:      // Scroll one page right.
	{
		// Get the page size. 
		SCROLLINFO   info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (m_nScrolHPos < maxpos)
			m_nScrolHPos = min(maxpos, m_nScrolHPos + (int)info.nPage);
	}
	break;
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		m_nScrolHPos = nPos;      // of the scroll box at the end of the drag operation.
		break;
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		m_nScrolHPos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	pScrollBar->SetScrollPos( m_nScrolHPos);
	m_wndPicPreview.Invalidate();
}


void CScreenShotDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos);
	maxpos = pScrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	m_nScrolVPos = pScrollBar->GetScrollPos();

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_TOP:      // Scroll to far left.
		m_nScrolVPos = minpos;
		break;
	case SB_BOTTOM:      // Scroll to far right.
		m_nScrolVPos = maxpos;
		break;
	case SB_ENDSCROLL:   // End scroll.
		break;
	case SB_LINEUP:      // Scroll left.
		if (m_nScrolVPos > minpos)
			m_nScrolVPos--;
		break;
	case SB_LINEDOWN:   // Scroll right.
		if (m_nScrolVPos < maxpos)
			m_nScrolVPos++;
		break;
	case SB_PAGEUP:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (m_nScrolVPos > minpos)
			m_nScrolVPos = max(minpos, m_nScrolVPos - (int)info.nPage);
	}
	break;
	case SB_PAGEDOWN:      // Scroll one page right.
	{
		// Get the page size. 
		SCROLLINFO   info;
		pScrollBar->GetScrollInfo(&info, SIF_ALL);

		if (m_nScrolVPos < maxpos)
			m_nScrolVPos = min(maxpos, m_nScrolVPos + (int)info.nPage);
	}
	break;
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		m_nScrolVPos = nPos;      // of the scroll box at the end of the drag operation.
		break;
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		m_nScrolVPos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	pScrollBar->SetScrollPos(m_nScrolVPos);
	m_wndPicPreview.Invalidate();
}
