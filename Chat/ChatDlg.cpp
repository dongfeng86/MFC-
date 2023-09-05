
// ChatDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "afxdialogex.h"
#include "AtlBase.h"
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CChatDlg::InitSocket()
{
	//创建数据报形式的套接字
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		MessageBox(_T("套接字创建失败！"));
		return FALSE;
	}

	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	addrSock.sin_addr.S_un.S_addr = INADDR_ANY;

	int iRet;
	iRet = bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == iRet)
	{
		MessageBox(_T("绑定失败"));
		closesocket(m_socket);
		return FALSE;
	}

	return TRUE;
}


void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_wndIPCtrl);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECVDATA, OnRecvData)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()

DWORD WINAPI RecvProc(__in  LPVOID lpParameter)
{
	SOCKET sock = ((SRecvParam*)lpParameter)->sock;
	HWND hWnd = ((SRecvParam*)lpParameter)->hwnd;

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);

	char recvBuf[200];
	char tempBuf[300];
	int iRet;
	while (true)
	{
		iRet = recvfrom(sock, recvBuf, 200, 0, (SOCKADDR*)&addrFrom, &len);
		if(SOCKET_ERROR==iRet)
			break;
		sprintf_s(tempBuf, "%s说：%s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		::PostMessage(hWnd, WM_RECVDATA, 0, (LPARAM)tempBuf);
	}
	return 0;
}

BOOL CChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitSocket();
	SRecvParam* pRecvParam = new SRecvParam;
	pRecvParam->sock = m_socket;
	pRecvParam->hwnd = m_hWnd;

	HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	CloseHandle(hThread);

	return TRUE;
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CChatDlg::OnPaint()
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CChatDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	//这块的转换函数有点意思
	CString str;
	str = (char*)lParam;
	CString strTemp;
	GetDlgItemText(IDC_EDT_RECV, strTemp);
	str += _T("\r\n");
	str += strTemp;
	SetDlgItemText(IDC_EDT_RECV, str);
	return 0;
}

void CChatDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwIP;
	m_wndIPCtrl.GetAddress(dwIP);

	SOCKADDR_IN addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6000);
	addrTo.sin_addr.S_un.S_addr = htonl(dwIP);

	CString strSend;
	GetDlgItemText(IDC_EDT_SEND, strSend);
	sendto(m_socket, CT2A(strSend), strlen(CT2A(strSend)) + 1, 0, (SOCKADDR*)&addrTo, sizeof(SOCKADDR));
	SetDlgItemText(IDC_EDT_SEND, _T(""));
}
