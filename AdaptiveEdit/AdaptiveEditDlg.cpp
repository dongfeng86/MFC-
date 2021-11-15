
// AdaptiveEditDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AdaptiveEdit.h"
#include "AdaptiveEditDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdaptiveEditDlg 对话框



CAdaptiveEditDlg::CAdaptiveEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_ADAPTIVEEDIT, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdaptiveEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_SIZEABLE, m_wndEdtSizeable);
}

BEGIN_MESSAGE_MAP(CAdaptiveEditDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDT_SIZEABLE, &CAdaptiveEditDlg::OnEnChangeEdtSizeable)
END_MESSAGE_MAP()

BOOL CAdaptiveEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAdaptiveEditDlg::OnPaint()
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
HCURSOR CAdaptiveEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAdaptiveEditDlg::OnEnChangeEdtSizeable()
{
	//查看目前编辑框文本到底多少行
	int iLineCount = m_wndEdtSizeable.GetLineCount();

	//获取每行文字的高度
	CClientDC dc(&m_wndEdtSizeable);
	CFont* pCurFont = m_wndEdtSizeable.GetFont();
	CFont* pOldFont = dc.SelectObject(pCurFont);
	TEXTMETRIC tmText;
	dc.GetTextMetrics(&tmText);
	int iTotalHeight = (iLineCount+1) * (tmText.tmHeight + tmText.tmExternalLeading);
	dc.SelectObject(pOldFont);

	//设置文本框的大小位置
	CRect rect;
	m_wndEdtSizeable.GetWindowRect(rect);
	ScreenToClient(rect);
	if (iTotalHeight > rect.Height())
	{
		rect.bottom = rect.top + iTotalHeight;
		m_wndEdtSizeable.MoveWindow(rect);
	}

	//额外写的这段程序是为了说明TRACE和aafxDump的使用
	int x = 1;
	int y = 16;
	float z = 32.0;
	TRACE(_T("This is a TRACE statement\n"));
	TRACE(_T("The value of x is %d\n"), x);
	TRACE(_T("x = %d and y = %d\n"), x, y);
	TRACE(_T("x = %d and y = %x and z = %f\n"), x, y, z);
	CRect rect22(10, 20, 30, 40);
#ifdef _DEBUG
	afxDump << "afxdump z=" << z <<"\n";	//这个输出有一大串，不知道为啥
#endif
}
