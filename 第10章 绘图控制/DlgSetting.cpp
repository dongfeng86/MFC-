// DlgSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphic.h"
#include "DlgSetting.h"

UINT CDlgSetting::m_nLineWidth = 0;
int CDlgSetting::m_nLineStyle = 0;

IMPLEMENT_DYNAMIC(CDlgSetting, CDialog)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{
	m_clr=RGB(255,0,0);
	m_brush.CreateSolidBrush(RGB(0,0,255));
}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LINEWIDTH, m_nLineWidth);
	DDX_Radio(pDX, IDC_RAD_1, m_nLineStyle);
}

BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	ON_EN_CHANGE(IDC_EDT_LINEWIDTH, &CDlgSetting::OnEnChangeEdtLinewidth)
	ON_BN_CLICKED(IDC_RAD_1, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_2, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_3, &CDlgSetting::OnBnClickedRad1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgSetting 消息处理程序

void CDlgSetting::OnEnChangeEdtLinewidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
}

void CDlgSetting::OnBnClickedRad1()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}

void CDlgSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	UpdateData();
	
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);

	ScreenToClient(rect);

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
}

//如何更改控件的背景和颜色
HBRUSH CDlgSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if(pWnd->GetDlgCtrlID()==IDC_LINESTYLE)
	{
		//经试验，这两句无效
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID()==IDC_EDT_LINEWIDTH)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(0,255,0));
		return m_brush;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
