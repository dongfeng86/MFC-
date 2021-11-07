
// AddTipsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AddTips.h"
#include "AddTipsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddTipsDlg 对话框



CAddTipsDlg::CAddTipsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDTIPS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddTipsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAddTipsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CAddTipsDlg 消息处理程序

BOOL CAddTipsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_wndTipContrl.Create(this);
	m_wndTipContrl.AddTool(this, _T("这是对话框"));
	m_wndTipContrl.AddTool(GetDlgItem(IDC_BTN_TIPS), _T("提示信息1：试验"));
	m_wndTipContrl.AddTool(GetDlgItem(IDC_BTN_TIPS2), _T("提示信息2：试验"));

	m_wndTipContrl.SetDelayTime(200);
	m_wndTipContrl.SetTipTextColor(RGB(0, 0, 0));//设置提示字体颜色
	m_wndTipContrl.SetTipBkColor(RGB(255, 255, 255));//设置提示背景颜色
	m_wndTipContrl.Activate(TRUE);    //最后别忘了激活状态

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAddTipsDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAddTipsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CAddTipsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE)
	{
		m_wndTipContrl.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
