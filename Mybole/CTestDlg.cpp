// CTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CTestDlg.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_bIsCreate(FALSE)
	, m_dNum1(0)
	, m_dNum2(0)
	, m_dNum3(0)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dNum1);
	DDX_Text(pDX, IDC_EDIT2, m_dNum2);
	DDX_Text(pDX, IDC_EDIT3, m_dNum3);
	DDX_Control(pDX, IDC_EDIT1, m_wndEdit1);
	DDX_Control(pDX, IDC_EDIT2, m_wndEdit2);
	DDX_Control(pDX, IDC_EDIT3, m_wndEdit3);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnBnClickedBtnAdd)
	ON_STN_CLICKED(IDC_STATIC1, &CTestDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��̬����һ����ť
	//���ǵ�һ�ַ�ʽ���ȽϷ���
	/*
	if(!m_bIsCreate)
	{
		m_bIsCreate = m_cBtn.Create(_T("ά��"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
			CRect(0,0,100,100),this,123);
	}
	else
	{
		m_cBtn.DestroyWindow();
		m_bIsCreate=FALSE;
	}
	*/

	/*
	//��̬������ť�����·����ǻ��ڶԴ��ھ�������������������ģ�ʵ����̫������
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
	*/


	//��ȡ�ؼ��е����֣���һ�ַ�����
	/*
	CString sNum1,sNum2,sNum3;
	//GetDlgItem(IDC_EDIT1)->GetWindowText(sNum1);  //��һ�ַ�ʽ
	//GetDlgItem(IDC_EDIT2)->GetWindowText(sNum2);
	GetDlgItemText(IDC_EDIT1,sNum1);                //�ڶ��ַ�ʽ
	GetDlgItemText(IDC_EDIT2,sNum2);
	
	double dNum1,dNum2,dNum3;
	dNum1=_wtof(sNum1);
	dNum2=_wtof(sNum2);
	dNum3=dNum1+dNum2;

	sNum3.Format(_T("%.1f"),dNum3);
	//GetDlgItem(IDC_EDIT3)->SetWindowText(sNum3);  //��һ�ַ�ʽ
	SetDlgItemText(IDC_EDIT3,sNum3);                //�ڶ��ַ�ʽ
	*/

	//��ȡ�ؼ��е����֣��ڶ��ַ�����
	/*
	UpdateData(TRUE);             //�ӶԻ����ȡ���ݣ���ϸ����
	m_dNum3=m_dNum1+m_dNum2;
	UpdateData(FALSE);            //�ñ���ֵ���¶Ի�������
	*/

	//��ȡ�ؼ��е����֣������ַ�����
	/*
	int iNum1,iNum2,iNum3;
	CString sEdit1,sEdit2,sEdit3;
	m_wndEdit1.GetWindowText(sEdit1);
	m_wndEdit2.GetWindowText(sEdit2);

	iNum1=_wtoi(sEdit1);
	iNum2=_wtoi(sEdit2);
	iNum3=iNum1+iNum2;
	sEdit3.Format(_T("%d"),iNum3);

	m_wndEdit3.SetWindowText(sEdit3);
	*/
	
	//������Ϣ���ƿؼ���ʾ�������ַ�����
	/*
	int iNum1,iNum2,iNum3;
	//CString sEdit1,sEdit2,sEdit3;
	TCHAR ch1[20];
	TCHAR ch2[20];
	TCHAR ch3[20];
	//::SendMessage(GetDlgItem(IDC_EDIT1)->m_hWnd,WM_GETTEXT,10,(LPARAM)sEdit1);
	//::SendMessage(m_wndEdit1.m_hWnd,WM_GETTEXT,10,(LPARAM)sEdit1);
	//����CWnd�ĳ�Ա����
	//GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT,10,(LPARAM)sEdit1);
	m_wndEdit1.SendMessage(WM_GETTEXT,20,(LPARAM)ch1);
	m_wndEdit2.SendMessage(WM_GETTEXT,20,(LPARAM)ch2);
	iNum1=_wtoi(ch1);
	iNum2=_wtoi(ch2);
	iNum3=iNum1+iNum2;
	_i64tow(iNum3,ch3,10);
	m_wndEdit3.SendMessage(WM_SETTEXT,0,(LPARAM)ch3);
	*/


	//������һ����������⣬������˼
	int iNum1,iNum2,iNum3;
	//CString sEdit1,sEdit2,sEdit3;
	CString ch1;
	CString ch2;
	CString ch3;
	m_wndEdit1.SendMessage(WM_GETTEXT,20,(LPARAM)((LPCTSTR)ch1));
	m_wndEdit2.SendMessage(WM_GETTEXT,20,(LPARAM)((LPCTSTR)ch2));
	iNum1=_wtoi(ch1);
	iNum2=_wtoi(ch2);
	iNum3=iNum1+iNum2;
	ch3.Format(_T("%d"),iNum3);
	m_wndEdit3.SendMessage(WM_SETTEXT,0,(LPARAM)((LPCTSTR)ch3));
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

