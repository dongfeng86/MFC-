// CTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CTestDlg.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_bIsCreate(FALSE)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnBnClickedBtnAdd)
	ON_STN_CLICKED(IDC_STATIC1, &CTestDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ǵ�һ�ַ�ʽ���ȽϷ���
	//if(!m_bIsCreate)
	//{
	//	m_bIsCreate = m_cBtn.Create(_T("ά��"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
	//		CRect(0,0,100,100),this,123);
	//}
	//else
	//{
	//	m_cBtn.DestroyWindow();
	//	m_bIsCreate=FALSE;
	//}

	//���·����ǻ��ڶԴ��ھ�������������������ģ�̫������
	//���CButton����Ĵ��ھ��ΪNULL���ʹ���һ��
	if(!m_cBtn.m_hWnd)
	{
		m_bIsCreate = m_cBtn.Create(_T("ά��"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
			CRect(0,0,100,100),this,123);
	}
	else
	{
		m_cBtn.DestroyWindow();
	}

}

void CTestDlg::OnStnClickedStatic1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	if(GetDlgItem(IDC_STATIC1)->GetWindowText(str),str==_T("Num1"))
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("��ֵ1"));
	}
	else
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("Num1"));
	}
}

