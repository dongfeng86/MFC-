// CTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CTestDlg.h"


// CTestDlg 对话框

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
	ON_BN_CLICKED(IDC_BTN_SHRINK, &CTestDlg::OnBnClickedBtnShrink)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//动态创建一个按钮
	//这是第一种方式，比较繁琐
	/*
	if(!m_bIsCreate)
	{
		m_bIsCreate = m_cBtn.Create(_T("维新"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
			CRect(0,0,100,100),this,123);
	}
	else
	{
		m_cBtn.DestroyWindow();
		m_bIsCreate=FALSE;
	}
	*/

	/*
	//动态创建按钮，以下方法是基于对窗口句柄的深刻理解所做出来的，实在是太厉害了
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
	*/


	//获取控件中的数字（第一种方法）
	/*
	CString sNum1,sNum2,sNum3;
	//GetDlgItem(IDC_EDIT1)->GetWindowText(sNum1);  //第一种方式
	//GetDlgItem(IDC_EDIT2)->GetWindowText(sNum2);
	GetDlgItemText(IDC_EDIT1,sNum1);                //第二种方式
	GetDlgItemText(IDC_EDIT2,sNum2);
	
	double dNum1,dNum2,dNum3;
	dNum1=_wtof(sNum1);
	dNum2=_wtof(sNum2);
	dNum3=dNum1+dNum2;

	sNum3.Format(_T("%.1f"),dNum3);
	//GetDlgItem(IDC_EDIT3)->SetWindowText(sNum3);  //第一种方式
	SetDlgItemText(IDC_EDIT3,sNum3);                //第二种方式
	*/

	//获取控件中的数字（第二种方法）
	/*
	UpdateData(TRUE);             //从对话框获取数据，更细变量
	m_dNum3=m_dNum1+m_dNum2;
	UpdateData(FALSE);            //用变量值更新对话框数据
	*/

	//获取控件中的数字（第三种方法）
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
	
	//利用消息控制控件显示（第四种方法）
	
	//int iNum1,iNum2,iNum3;
	////CString sEdit1,sEdit2,sEdit3;
	//TCHAR ch1[20];
	//TCHAR ch2[20];
	//TCHAR ch3[20];
	//::SendMessage(GetDlgItem(IDC_EDIT1)->m_hWnd,WM_GETTEXT,10,(LPARAM)ch1);
	//::SendMessage(m_wndEdit2.m_hWnd,WM_GETTEXT,10,(LPARAM)ch2);
	////利用CWnd的成员函数
	////GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT,10,(LPARAM)sEdit1);
	////m_wndEdit1.SendMessage(WM_GETTEXT,20,(LPARAM)ch1);
	////m_wndEdit2.SendMessage(WM_GETTEXT,20,(LPARAM)ch2);
	//iNum1=_wtoi(ch1);
	//iNum2=_wtoi(ch2);
	//iNum3=iNum1+iNum2;
	//_i64tow(iNum3,ch3,10);
	//m_wndEdit3.SendMessage(WM_SETTEXT,0,(LPARAM)ch3);
	


	////下面是一个奇妙的问题，匪夷所思
	//int iNum1,iNum2,iNum3;
	////CString sEdit1,sEdit2,sEdit3;
	//CString ch1;
	//CString ch2;
	//CString ch3;
	//m_wndEdit1.SendMessage(WM_GETTEXT,20,(LPARAM)((LPCTSTR)ch1));
	//m_wndEdit2.SendMessage(WM_GETTEXT,20,(LPARAM)((LPCTSTR)ch2));
	//iNum1=_wtoi(ch1);
	//iNum2=_wtoi(ch2);
	//iNum3=iNum1+iNum2;
	//ch3.Format(_T("%d"),iNum3);
	//m_wndEdit3.SendMessage(WM_SETTEXT,0,(LPARAM)((LPCTSTR)ch3));


	//第7种方法，利用给控件发送消息的函数
	TCHAR ch1[20];
	TCHAR ch2[20];
	TCHAR ch3[20];
	SendDlgItemMessage(IDC_EDIT1,WM_GETTEXT,20,(LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2,WM_GETTEXT,20,(LPARAM)ch2);

	int iNum1,iNum2,iNum3;
	iNum1=_wtoi(ch1);
	iNum2=_wtoi(ch2);
	iNum3=iNum1+iNum2;
	_i64tow(iNum3,ch3,10);
	SendDlgItemMessage(IDC_EDIT3,WM_SETTEXT,20,(LPARAM)ch3);
	SendDlgItemMessage(IDC_EDIT3,EM_SETSEL,0,-1);
	m_wndEdit3.SetFocus();            //必须设置焦点，否则无法显示选中效果

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


void CTestDlg::OnBnClickedBtnShrink()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(GetDlgItemText(IDC_BTN_SHRINK,str),str==_T("收缩<<"))
	{
		SetDlgItemText(IDC_BTN_SHRINK,_T("扩展>>"));
	}
	else
	{
		SetDlgItemText(IDC_BTN_SHRINK,_T("收缩<<"));
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if(rectLarge.IsRectNull())
	{
		CRect rectSeprator;
		GetWindowRect(& rectLarge);
		GetDlgItem(IDC_STATIC_SEPARATOR)->GetWindowRect(&rectSeprator);

		rectSmall.left=rectLarge.left;
		rectSmall.top=rectLarge.top;
		rectSmall.right=rectLarge.right;
		rectSmall.bottom=rectSeprator.bottom;
	}

	if(str==_T("收缩<<"))
	{
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),
			SWP_NOMOVE|SWP_NOZORDER);
	}
}

void CTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();

	//static HWND pPreFocus=::GetFocus();
	//pPreFocus=::GetNextWindow(pPreFocus,GW_HWNDNEXT);
	//::SetFocus(pPreFocus);
	//GetFocus()->GetNextWindow()->SetFocus();

	//寻找下一个控件，再把它设为焦点
	GetNextDlgTabItem(GetFocus())->SetFocus();
	//OnOK();
}
//
//WNDPROC prevProc;
//
//LRESULT CALLBACK WinSunProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
//{
//	if(uMsg==WM_CHAR && wParam==0x0d)
//	{
//		//::SetFocus(::GetNextWindow(/*::GetDlgItem(::FindWindow(_T("CTestDlg"),NULL),IDC_EDIT1)*/hwnd,GW_HWNDNEXT));
//		//::SetFocus(::GetWindow(hwnd,GW_HWNDNEXT));
//		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd),hwnd,FALSE));
//		return 1;
//	}
//	else
//	{
//		return prevProc(hwnd,uMsg,wParam,lParam);
//	}
//}

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//prevProc=(WNDPROC)SetWindowLong(GetDlgItem(IDC_EDIT1)->m_hWnd,GWL_WNDPROC,(long)WinSunProc);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
