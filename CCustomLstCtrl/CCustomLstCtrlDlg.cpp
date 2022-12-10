
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
	ON_CBN_DROPDOWN(IDC_COMBO1, &CCCustomLstCtrlDlg::OnCbnDropdownCombo1)
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
	m_wndLst.ModifyStyle(0, LVS_OWNERDRAWFIXED);
	m_wndLst.SetExtendedStyle( LVS_EX_GRIDLINES);
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

	m_wndLst.SetRowHeigt(28);
	std::vector<CString> arList;
	arList.push_back(_T("nihao"));
	arList.push_back(_T("或者"));
	arList.push_back(_T("新鲜"));
	m_wndLst.SetCellDropList(0, 0, arList);

	arList.clear();
	arList.push_back(_T("nihao"));
	arList.push_back(_T("或者"));
	arList.push_back(_T("新鲜"));
	m_wndLst.SetCellDropList(0, 1, arList);

	arList.clear();
	m_wndLst.SetCellDropList(0, 2, arList);

	arList.clear();
	arList.push_back(_T("abc"));
	arList.push_back(_T("或者"));
	arList.push_back(_T("deg"));
	m_wndLst.SetCellDropList(1, 0, arList, (CDialog*)0x11);


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

	//让我们看一下对话框的尺寸对吗
	//经查，无论对话框模板如何修改字体，GetDialogBaseUnits总是返回相同的值
	//MapDialogRect与GetWindowRect返回的值也不完全相同
	CRect rect1;
	GetWindowRect(rect1);
	int cxChar = LOWORD(GetDialogBaseUnits());
	int cyChar = HIWORD(GetDialogBaseUnits());

	int pixelX = MulDiv(320, cxChar, 4);
	int pixelY = MulDiv(200, cyChar, 8);

	CRect rect2(0,0,320,200);
	MapDialogRect(rect2);
	

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


void CCCustomLstCtrlDlg::OnCbnDropdownCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
