// DlgSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "Graphic.h"
#include "DlgSetting.h"


// CDlgSetting 对话框

IMPLEMENT_DYNAMIC(CDlgSetting, CDialog)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{

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


UINT CDlgSetting::m_nLineWidth = 0;

int CDlgSetting::m_nLineStyle = 0;

BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	ON_EN_CHANGE(IDC_EDT_LINEWIDTH, &CDlgSetting::OnEnChangeEdtLinewidth)
	ON_BN_CLICKED(IDC_RAD_1, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_2, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_3, &CDlgSetting::OnBnClickedRad1)
	ON_WM_PAINT()
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
	
	CPen pen(m_nLineStyle,m_nLineWidth,RGB(255,0,0));
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
}
