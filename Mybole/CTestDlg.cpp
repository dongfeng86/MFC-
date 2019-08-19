// CTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CTestDlg.h"


// CTestDlg 对话框

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


// CTestDlg 消息处理程序

void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//这是第一种方式，比较繁琐
	//if(!m_bIsCreate)
	//{
	//	m_bIsCreate = m_cBtn.Create(_T("维新"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
	//		CRect(0,0,100,100),this,123);
	//}
	//else
	//{
	//	m_cBtn.DestroyWindow();
	//	m_bIsCreate=FALSE;
	//}

	//以下方法是基于对窗口句柄的深刻理解所做出来的，太厉害了
	//如果CButton对象的窗口句柄为NULL，就创建一个
	if(!m_cBtn.m_hWnd)
	{
		m_bIsCreate = m_cBtn.Create(_T("维新"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
			CRect(0,0,100,100),this,123);
	}
	else
	{
		m_cBtn.DestroyWindow();
	}

}

void CTestDlg::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(GetDlgItem(IDC_STATIC1)->GetWindowText(str),str==_T("Num1"))
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("数值1"));
	}
	else
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("Num1"));
	}
}

