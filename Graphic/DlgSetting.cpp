// DlgSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Graphic.h"
#include "DlgSetting.h"


// CDlgSetting �Ի���

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


// CDlgSetting ��Ϣ�������

void CDlgSetting::OnEnChangeEdtLinewidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}

void CDlgSetting::OnBnClickedRad1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}

void CDlgSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	
	CPen pen(m_nLineStyle,m_nLineWidth,RGB(255,0,0));
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
}
