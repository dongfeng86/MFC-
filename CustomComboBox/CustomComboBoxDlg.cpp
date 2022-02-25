
// CustomComboBoxDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CustomComboBox.h"
#include "CustomComboBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomComboBoxDlg 对话框



CCustomComboBoxDlg::CCustomComboBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUSTOMCOMBOBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomComboBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_wndCmbCustom);
}

BEGIN_MESSAGE_MAP(CCustomComboBoxDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CCustomComboBoxDlg::OnCbnKillfocusCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomComboBoxDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCustomComboBoxDlg 消息处理程序

BOOL CCustomComboBoxDlg::OnInitDialog()
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
	int iiiii;
	iiiii = m_wndCmbCustom.InsertString(0, _T("hello"));
	iiiii = m_wndCmbCustom.InsertString(1, _T("he"));
	iiiii = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetItemHeight(-1);
	//iiiii= ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetItemHeight(-1);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetItemHeight(-1, iiiii);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCustomComboBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCustomComboBoxDlg::OnPaint()
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
HCURSOR CCustomComboBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


IMPLEMENT_DYNAMIC(CCustomComboBox, CComboBox)


CCustomComboBox::CCustomComboBox()
	:CComboBox()
{}

CCustomComboBox::~CCustomComboBox()
{}

void CCustomComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	LPCTSTR lpszText = (LPCTSTR)lpDrawItemStruct->itemData;
	CString sItem;
	GetLBText(lpDrawItemStruct->itemID,sItem);
	if (!sItem.IsEmpty())
	{
		int iCount = GetCount();	//判断这个列表框一共有多少项

		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		COLORREF crOldTextColor = dc.GetTextColor();	//完成绘图后恢复DC里的值
		COLORREF crOldBkColor = dc.GetBkColor();
		//处理最后一个项目，设置其背景和文字
		if ((lpDrawItemStruct->itemAction & ODA_SELECT) &&
			(lpDrawItemStruct->itemState  & ODS_SELECTED))
		{
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			if (iCount && lpDrawItemStruct->itemID == iCount - 1)
			{
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_3DFACE));	//获取对话框背景颜色
				dc.DrawEdge(&lpDrawItemStruct->rcItem, EDGE_BUMP, BF_RECT);
			}
			else
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
		}

		dc.DrawText(sItem, sItem.GetLength(), &lpDrawItemStruct->rcItem,
			DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		dc.SetTextColor(crOldTextColor);
		dc.SetBkColor(crOldBkColor);
		dc.Detach();
	}
}

void CCustomComboBoxDlg::OnCbnKillfocusCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_wndCmbCustom.GetWindowText(str);
	m_wndCmbCustom.InsertString(0, str);
}

void CCustomComboBoxDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
