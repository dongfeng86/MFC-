
// CCustomLstCtrlDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CCustomLstCtrl.h"
#include "CCustomLstCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _ID_DYN_CREATE_EDIT_ 10000

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


// CCCustomLstCtrlDlg 对话框



CCCustomLstCtrlDlg::CCCustomLstCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CCUSTOMLSTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCustomLstCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_CTRL, m_wndLst);
}

BEGIN_MESSAGE_MAP(CCCustomLstCtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LST_CTRL, &CCCustomLstCtrlDlg::OnNMClickLstCtrl)
END_MESSAGE_MAP()


// CCCustomLstCtrlDlg 消息处理程序

BOOL CCCustomLstCtrlDlg::OnInitDialog()
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
	m_wndLst.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_wndLst.GetWindowRect(rect);
	m_wndLst.InsertColumn(0, _T("逻辑"), 0, rect.Width() * 1 / 3);
	m_wndLst.InsertColumn(1, _T("second"), 0, rect.Width() * 1 / 3);
	m_wndLst.InsertColumn(2, _T("third"), 0, rect.Width() * 1 / 3);


	for (int i = 0; i < 5; i++)
	{
		m_wndLst.InsertItem(i, _T("你好"));
		m_wndLst.SetItemText(i, 1, _T("足球"));
		m_wndLst.SetItemText(i, 2, _T("篮球球"));

	}

	//找到列表头
	CHeaderCtrl* pHeadCtrl = m_wndLst.GetHeaderCtrl();
	m_wndCustomHeadCtrl.SubclassWindow(pHeadCtrl->GetSafeHwnd());

	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for (int i = 0; i < m_wndCustomHeadCtrl.GetItemCount(); i++)
	{
		m_wndCustomHeadCtrl.GetItem(i, &hdItem);

		hdItem.fmt |= HDF_OWNERDRAW;

		m_wndCustomHeadCtrl.SetItem(i, &hdItem);
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCCustomLstCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCCustomLstCtrlDlg::OnPaint()
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
HCURSOR CCCustomLstCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCCustomLstCtrlDlg::OnNMClickLstCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//进行单击检测，这个结构已经被扩展为能够适应子项的单击检测。
	LVHITTESTINFO cHitTest;
	cHitTest.pt = pNMItemActivate->ptAction;

	CRect rect11;


	if (-1 != m_wndLst.SubItemHitTest(&cHitTest))	//检测给定坐标位于哪个单元格上
	{
		if (cHitTest.flags & LVHT_ONITEMLABEL)
		{
			//获取单元格信息
			int iX, iY;
			iX = cHitTest.iItem;
			iY = cHitTest.iSubItem;

			CRect rect;	//单元格的尺寸
			m_wndLst.GetSubItemRect(iX, iY, LVIR_LABEL, rect);	//注意，这个坐标是相对于ListCtrl左上角的
			CString sValue = m_wndLst.GetItemText(iX, iY);	//获取当前单元格的内容

			//动态创建编辑框
			if (!m_wndCmbTemp.m_hWnd)
			{
				m_wndCmbTemp.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN, rect, &m_wndLst, _ID_DYN_CREATE_EDIT_);
				m_wndCmbTemp.SetFont(m_wndLst.GetFont(), FALSE);		//设置编辑框的字体
			}

			m_wndCmbTemp.SetWindowText(sValue);
			m_wndCmbTemp.MoveWindow(rect);
			m_wndCmbTemp.ShowWindow(SW_SHOW);
			m_wndCmbTemp.InsertString(0, _T("hee"));
			m_wndCmbTemp.AddString(_T("dafds"));


			int iLength = sValue.GetLength();
			//m_wndEdt.SetSel(0, iLength, FALSE);	//设置光标选中所有文字
			m_wndCmbTemp.SetFocus();

			m_wndCmbTemp.GetWindowRect(rect11);
		}
	}

	*pResult = 0;
}
