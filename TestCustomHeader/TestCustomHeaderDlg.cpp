
// TestCustomHeaderDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestCustomHeader.h"
#include "TestCustomHeaderDlg.h"
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


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TESTCUSTOMHEADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_MAIN, m_wndLstMain);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
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
	m_wndLstMain.GetClientRect(rect);
	m_wndLstMain.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, rect.Width() / 3);
	m_wndLstMain.InsertColumn(1, _T("班级"), LVCFMT_LEFT, rect.Width() / 3);
	m_wndLstMain.InsertColumn(2, _T("学号"), LVCFMT_LEFT, rect.Width() / 3);

	m_wndLstMain.InsertItem(0, _T("张三"));
	m_wndLstMain.SetItemText(0, 1, _T("一班"));
	m_wndLstMain.SetItemText(0, 2, _T("001"));

	m_wndLstMain.InsertItem(1, _T("李四"));
	m_wndLstMain.SetItemText(1, 1, _T("一班"));
	m_wndLstMain.SetItemText(1, 2, _T("002"));

	m_wndLstMain.InsertItem(2, _T("王五"));
	m_wndLstMain.SetItemText(2, 1, _T("一班"));
	m_wndLstMain.SetItemText(2, 2, _T("003"));

	m_wndLstMain.SetExtendedStyle(LVS_EX_GRIDLINES);

	CHeaderCtrl* pHeader = m_wndLstMain.GetHeaderCtrl();
	if(pHeader)
		m_wndHeader.SubclassWindow(pHeader->GetSafeHwnd());
	HDITEM hdItem;
	hdItem.mask = HDI_FORMAT;
	for (int i = 0; i < m_wndHeader.GetItemCount(); i++)
	{
		m_wndHeader.GetItem(i, &hdItem);
		hdItem.fmt |= HDF_OWNERDRAW;
		m_wndHeader.SetItem(i, &hdItem);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint()
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd* pWnd = NULL;
	CRect rect;
	pWnd = GetDlgItem(IDCANCEL);
	if (pWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		int xOffset = cx - 57*1.5;
		int yOffset = cy - 21*1.5;
		rect.MoveToXY(xOffset, yOffset);
		pWnd->MoveWindow(rect);

		pWnd = GetDlgItem(IDOK);
		if (pWnd)
		{
			rect.OffsetRect(-54*1.5, 0);
			pWnd->MoveWindow(rect);
		}
	}

	if (m_wndLstMain.GetSafeHwnd())
	{
		m_wndLstMain.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right = cx - 7 * 1.5;
		rect.bottom = cy - 26 * 1.5;
		m_wndLstMain.MoveWindow(rect);

		m_wndLstMain.SetColumnWidth(0, rect.Width() / 3);
		m_wndLstMain.SetColumnWidth(1, rect.Width() / 3);
		m_wndLstMain.SetColumnWidth(2, rect.Width() / 3);
	}
}
