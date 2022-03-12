
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


// CSWColorComboBox
IMPLEMENT_DYNAMIC(CSWColorComboBox, CComboBox)
CSWColorComboBox::TColorProperty CSWColorComboBox::s_clrPropertys[MAX_COLOR_COUNT] =
{
	TColorProperty(RGB(0x00, 0x00, 0x00), _T("黑色(Black)")),
	TColorProperty(RGB(0x80, 0x00, 0x00), _T("褐红色(Maroon)")),
	TColorProperty(RGB(0x00, 0x80, 0x00), _T("调和绿(Green)")),
	TColorProperty(RGB(0x80, 0x80, 0x00), _T("橄榄色(Olive)")),
	TColorProperty(RGB(0x00, 0x00, 0x80), _T("藏青色(Navy)")),
	TColorProperty(RGB(0x80, 0x00, 0x80), _T("紫色(Purple)")),
	TColorProperty(RGB(0x00, 0x80, 0x80), _T("鸭翅绿(Teal)")),
	TColorProperty(RGB(0x80, 0x80, 0x80), _T("灰色(Gray)")),
	TColorProperty(RGB(0xC0, 0xC0, 0xC0), _T("银色(Silver)")),
	TColorProperty(RGB(0xFF, 0x00, 0x00), _T("红色(Red)")),
	TColorProperty(RGB(0x00, 0xFF, 0x00),_T("绿色(Lime)")),
	TColorProperty(RGB(0xFF, 0xFF, 0x00), _T("黄色(Yellow)")),
	TColorProperty(RGB(0x00, 0x00, 0xFF), _T("蓝色(Blue)")),
	TColorProperty(RGB(0xFF, 0x00, 0xFF), _T("紫红色(Fushcia)")),
	TColorProperty(RGB(0x00, 0xFF, 0xFF),_T("青色(Aqua)")),
	TColorProperty(RGB(0xFF, 0xFF, 0xFF), _T("白色(White)")),
};
CSWColorComboBox::CSWColorComboBox()
{
}

CSWColorComboBox::~CSWColorComboBox()
{
}

BEGIN_MESSAGE_MAP(CSWColorComboBox, CComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CSWColorComboBox::CommonConstruct(void)
{
	for (int nIndex = 0; nIndex < MAX_COLOR_COUNT; nIndex++)
	{
		int nItem = AddString(s_clrPropertys[nIndex].m_szName);
		if (nItem == CB_ERRSPACE)
			break;
		else
			SetItemData(nItem, s_clrPropertys[nItem].m_clrColor);
	}
}

void CSWColorComboBox::DrawItem(LPDRAWITEMSTRUCT pDIStruct)
{
	CDC dc;
	if (!dc.Attach(pDIStruct->hDC))
		return;

	CString strName;
	CRect rItemRect(pDIStruct->rcItem);
	CRect rcFrame(rItemRect);
	CRect rcText(rcFrame);

	// 颜色边框画刷
	CBrush brFrameBrush;
	brFrameBrush.CreateStockObject(BLACK_BRUSH);

	int nFrameWidth = 0;
	int nItem = pDIStruct->itemID;
	int nAction = pDIStruct->itemAction;
	int nState = pDIStruct->itemState;
	COLORREF clrColor = 0;
	COLORREF clrNormal = GetSysColor(COLOR_WINDOW);
	COLORREF clrSelected = GetSysColor(COLOR_HIGHLIGHT);
	COLORREF clrText = GetSysColor(COLOR_WINDOWTEXT);

	// 颜色框宽度
	nFrameWidth = 40;
	if (nState & ODS_SELECTED)
	{
		dc.SetTextColor((0x00FFFFFF & ~(clrText)));
		dc.SetBkColor(clrSelected);
		dc.FillSolidRect(&rcFrame, clrSelected);
	}
	else
	{
		dc.SetTextColor(clrText);
		dc.SetBkColor(clrNormal);
		if (pDIStruct->itemAction & ODA_DRAWENTIRE
			&& pDIStruct->itemState & ODS_COMBOBOXEDIT)
			dc.FillSolidRect(&rcFrame, ::GetSysColor(COLOR_BTNSHADOW));
		else
			dc.FillSolidRect(&rcFrame, clrNormal);
	}

	if (nState & ODS_FOCUS)
		dc.DrawFocusRect(&rItemRect);

	rcFrame.left += 2;
	rcFrame.right = nFrameWidth;
	rcFrame.top += 2;
	rcText.left += (nFrameWidth + 2);
	rcText.DeflateRect(CSize(2, 2));

	if (nItem != -1)
	{
		GetLBText(nItem, strName);
		if (nState & ODS_DISABLED)
		{
			clrColor = GetSysColor(COLOR_INACTIVECAPTIONTEXT);
			dc.SetTextColor(clrColor);
		}
		else
		{
			clrColor = GetItemData(nItem);
		}

		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(rcText.left, rcText.top, strName);
		if (clrColor != RGB(0, 0, 1))
		{
			dc.FillSolidRect(&rcFrame, clrColor);
			dc.FrameRect(&rcFrame, &brFrameBrush);
		}
	}

	dc.Detach();
}

COLORREF CSWColorComboBox::GetSelColor()
{
	int nSelIndex = GetCurSel();
	if (nSelIndex == CB_ERR)
		return RGB(0, 0, 0);

	return GetItemData(nSelIndex);
}

void CSWColorComboBox::SelectColor(COLORREF color)
{
	int nCount = GetCount();
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		if (color == GetItemData(nIndex))
			SetCurSel(nIndex);
	}
}

void CSWColorComboBox::SelectColor(LPCTSTR lpszName)
{
	int nCount = GetCount();
	CString sColorName;
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		GetLBText(nIndex, sColorName);
		if (!sColorName.CompareNoCase(lpszName))
			SetCurSel(nIndex);
	}
}

void CSWColorComboBox::DeleteColor(LPCTSTR lpszName)
{
	int nCount = GetCount();
	CString strColorName;
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		GetLBText(nIndex, strColorName);
		if (!strColorName.CompareNoCase(lpszName))
		{
			DeleteString(nIndex);
			break;
		}
	}
}

void CSWColorComboBox::DeleteColor(COLORREF color)
{
	int nCount = GetCount();
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		if (color == GetItemData(nIndex))
		{
			DeleteString(nIndex);
			break;
		}
	}
}

int CSWColorComboBox::AddColor(LPCTSTR lpszName, COLORREF color)
{
	int nIndex = InsertString(-1, lpszName);
	if (nIndex != CB_ERR)
		SetItemData(nIndex, color);

	return nIndex;
}

void CSWColorComboBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CComboBox::PreSubclassWindow();
	CommonConstruct();
	SetCurSel(0);
}


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
	//DDX_Control(pDX, IDC_COMBO2, m_wndComboNorml);
	//DDX_Control(pDX, IDC_CMB_EXAMPLE, m_wndCmbNew);
}

BEGIN_MESSAGE_MAP(CCustomComboBoxDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CCustomComboBoxDlg::OnCbnKillfocusCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomComboBoxDlg::OnCbnSelchangeCombo1)
	ON_WM_DRAWITEM()
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
	m_wndCmbCustom.InsertString(0, _T("hello"));
	m_wndCmbCustom.InsertString(1, _T("he"));
	m_wndCmbCustom.InsertString(1, _T("h"));


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
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	COLORREF crOldTextColor = dc.GetTextColor();	//完成绘图后恢复DC里的值
	COLORREF crOldBkColor = dc.GetBkColor();

	// 选中一项，包括重绘编辑框和下拉列表某一项
	if (lpDrawItemStruct->itemState  & ODS_SELECTED)
	{
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	// 控件获取焦点
	else if (lpDrawItemStruct->itemState  & ODS_FOCUS)
	{
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		//绘制常态下的编辑框
		if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE &&
			lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT)
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_BTNSHADOW));
		//绘制常态下的下拉列表
		else
		{
			int iCount = GetCount();
			if (iCount && lpDrawItemStruct->itemID == iCount - 1)	//绘制最后一项
			{
				CRect rect = lpDrawItemStruct->rcItem;
				//dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_3DFACE));	//获取对话框背景颜色
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(0,255,0));	//为了表示清楚，此处显示红色
				dc.DrawEdge(&lpDrawItemStruct->rcItem, EDGE_BUMP, BF_RECT);	//绘制一个矩形框
			}
			else   //绘制除最后一项的其他项
				dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
		}
	}

	CString sItem;
	//最后一项被选中后不在编辑框中绘制文本
	if (lpDrawItemStruct->itemID != -1 &&
		!(lpDrawItemStruct->itemID == GetCount() - 1 && lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT))
	{
		GetLBText(lpDrawItemStruct->itemID, sItem);
		dc.DrawText(sItem, sItem.GetLength(), &lpDrawItemStruct->rcItem,
			DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	}

	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);
	dc.Detach();
}


void CCustomComboBoxDlg::OnCbnKillfocusCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CCustomComboBoxDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCustomComboBoxDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
