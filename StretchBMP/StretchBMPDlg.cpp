
// StretchBMPDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "StretchBMP.h"
#include "StretchBMPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CStretchBMPDlg 对话框



CStretchBMPDlg::CStretchBMPDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_STRETCHBMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStretchBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStretchBMPDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FIRST, &OnBtn1)	//消息映射
	ON_COMMAND(ID_SECOND, &OnBtn2)	//消息映射
END_MESSAGE_MAP()


// CStretchBMPDlg 消息处理程序

//屏幕缩放比例
double ScreenScale()
{
	double dXinchZoom = 1;
	HDC hDC = ::GetDC(HWND(NULL));
	int cxInch = ::GetDeviceCaps(hDC, LOGPIXELSX);
	dXinchZoom = cxInch / 96.0;
	::ReleaseDC(HWND(NULL), hDC);
	return dXinchZoom;
}

//按照比例拉伸位图
void StretchBitmap(CBitmap* pDestBitmap, CBitmap* pSrcBitmap, double dScale)
{
	//获取原位图尺寸信息
	BITMAP bmpInfo;
	pSrcBitmap->GetBitmap(&bmpInfo);
	int nWidth = bmpInfo.bmWidth;
	int nHeight = bmpInfo.bmHeight;

	//创建内存兼容DC
	CDC dcSrcMem, dcDestMem;	//两个内存兼容DC
	CDC dcDisplay;
	dcDisplay.CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
	dcSrcMem.CreateCompatibleDC(&dcDisplay);
	dcDestMem.CreateCompatibleDC(&dcDisplay);
	pDestBitmap->CreateCompatibleBitmap(&dcDisplay, nWidth*dScale, nHeight*dScale);
	dcDisplay.DeleteDC();

	//拉伸复制位图
	CBitmap* pOldSrcBitmap = dcSrcMem.SelectObject(pSrcBitmap);
	CBitmap* pOldDestBitmap = dcDestMem.SelectObject(pDestBitmap);
	dcDestMem.StretchBlt(0, 0, nWidth*dScale, nHeight*dScale, 
		&dcSrcMem, 0, 0, nWidth, nHeight, SRCCOPY);
	dcSrcMem.SelectObject(pOldSrcBitmap);
	dcDestMem.SelectObject(pOldDestBitmap);
}

BOOL CStretchBMPDlg::OnInitDialog()
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
	m_wndToolBar.Create(WS_CHILD | WS_VISIBLE | CCS_TOP | TBSTYLE_TOOLTIPS
		| TBSTYLE_FLAT | CCS_ADJUSTABLE, CRect(0, 0, 0, 0), this, IDB_TOOLBAR);
	TBBUTTON* pButton = new TBBUTTON[3];

	memset(&pButton[0], NULL, sizeof(TBBUTTON));
	pButton[0].iBitmap = 0;
	pButton[0].idCommand = ID_FIRST;
	pButton[0].fsStyle = TBSTYLE_CHECKGROUP;
	pButton[0].fsState = TBSTATE_ENABLED;

	memset(&pButton[1], NULL, sizeof(TBBUTTON));
	pButton[1].iBitmap = 0;
	pButton[1].idCommand = 0;
	pButton[1].fsStyle = TBSTYLE_SEP | TBSTYLE_CHECKGROUP;

	memset(&pButton[2], NULL, sizeof(TBBUTTON));
	pButton[2].iBitmap = 1;
	pButton[2].idCommand = ID_SECOND;
	pButton[2].fsStyle = TBSTYLE_CHECKGROUP;
	pButton[2].fsState = TBSTATE_ENABLED;

	double dScale = ScreenScale();
	CSize size(16 * dScale, 16 * dScale);
	m_wndToolBar.SetButtonSize(size);
	m_wndToolBar.AddButtons(3, pButton);
	delete[] pButton;
	m_wndToolBar.SetBitmapSize(size);

	CBitmap bmpSrc;
	bmpSrc.LoadBitmap(IDB_TOOLBAR);
	StretchBitmap(&m_bmpToolBar, &bmpSrc, dScale);

	m_wndToolBar.AddBitmap(2, &m_bmpToolBar);
	m_wndToolBar.AutoSize();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStretchBMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStretchBMPDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStretchBMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStretchBMPDlg::OnBtn1(void)
{
	MessageBox(_T("Press 1st button!"));
}

void CStretchBMPDlg::OnBtn2(void)
{
	MessageBox(_T("Press 2nd button!"));
}

