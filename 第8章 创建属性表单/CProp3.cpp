// CProp3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CProp3.h"


// CProp3 �Ի���

IMPLEMENT_DYNAMIC(CProp3, CPropertyPage)

CProp3::CProp3()
	: CPropertyPage(CProp3::IDD)
{

}

CProp3::~CProp3()
{
}

void CProp3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProp3, CPropertyPage)
END_MESSAGE_MAP()


// CProp3 ��Ϣ�������

BOOL CProp3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_FINISH|PSWIZB_FINISH);

	return CPropertyPage::OnSetActive();
}

BOOL CProp3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CComboBox *)GetDlgItem(IDC_COMBO2))->AddString(_T("1000Ԫ����"));
	((CComboBox *)GetDlgItem(IDC_COMBO2))->AddString(_T("1000~2000"));
	((CComboBox *)GetDlgItem(IDC_COMBO2))->AddString(_T("2000~3000"));
	((CComboBox *)GetDlgItem(IDC_COMBO2))->AddString(_T("3000Ԫ����"));

	((CComboBox *)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CProp3::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���

	int n=((CComboBox *)GetDlgItem(IDC_COMBO2))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO2))->GetLBText(n,m_strSalary);

	return CPropertyPage::OnWizardFinish();
}
