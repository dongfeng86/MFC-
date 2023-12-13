
// ChatAsyncDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ChatAsync.h"
#include "ChatAsyncDlg.h"
#include "afxdialogex.h"
#include <AtlBase.h>
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChatAsyncDlg 对话框



CChatAsyncDlg::CChatAsyncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATASYNC_DIALOG, pParent)
	, m_socket(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CChatAsyncDlg::~CChatAsyncDlg()
{
	if (m_socket)
		closesocket(m_socket);	//关闭套接字
}

void CChatAsyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatAsyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SOCK,OnSock)
	ON_BN_CLICKED(IDC_BTN_SEND, &CChatAsyncDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CChatAsyncDlg 消息处理程序

BOOL CChatAsyncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatAsyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatAsyncDlg::OnPaint()
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
HCURSOR CChatAsyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CChatAsyncDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case FD_READ:
	{
		CString str;
		CString strTemp;
		WSABUF wsabuf;
		wsabuf.buf = new char[200];
		wsabuf.len = 200;
		DWORD dwRead;
		DWORD dwFlag = 0;
		SOCKADDR_IN addrFrom;
		int len = sizeof(SOCKADDR);
		if (SOCKET_ERROR == WSARecvFrom(m_socket, &wsabuf, 1, &dwRead, &dwFlag,
			(SOCKADDR*)&addrFrom, &len, NULL, NULL))
		{
			MessageBox(_T("接受数据失败！"));
			return 0;
		}

		HOSTENT* pHost;
		pHost = gethostbyaddr((char*)&addrFrom.sin_addr.S_un.S_addr, 4, AF_INET);

		//注意，这里面从char*→CSTring，费了一些工夫，CString构造函数里面不能将char*转为CString，
		//但是赋值函数可以，神奇
		CString psz1;
		//psz1=inet_ntoa(addrFrom.sin_addr);
		psz1 = pHost->h_name;
		CString psz2;
		psz2 = CA2T(wsabuf.buf);
		str.Format(_T("%s说：%s"), psz1, psz2);
		str += _T("\r\n");
		GetDlgItemText(IDC_EDT_RECV, strTemp);
		str += strTemp;
		SetDlgItemText(IDC_EDT_RECV, str);
		break;
	}
	default:
		break;
	}
	return 0;
}

BOOL CChatAsyncDlg::InitSocket()
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
	if (INVALID_SOCKET == m_socket)
	{
		MessageBox(_T("创建套接字失败!"));
		return FALSE;
	}

	SOCKADDR_IN addrSock;
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);

	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR)))
	{
		MessageBox(_T("绑定失败!"));
		return FALSE;
	}

	if (SOCKET_ERROR == WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ))
	//if (SOCKET_ERROR == WSAEventSelect(m_socket, m_hWnd, UM_SOCK, FD_READ))
	{
		MessageBox(_T("注册网络读取事件失败!"));
		return FALSE;
	}

	return TRUE;
}


void CChatAsyncDlg::OnBnClickedBtnSend()
{
	USES_CONVERSION;

	DWORD dwIP;
	CString strSend;
	WSABUF wsaBuf;
	DWORD dwSend;
	int len;
	SOCKADDR_IN addrTo;
	CString sHostName;
	HOSTENT* pHost;
	if (GetDlgItemText(IDC_EDT_HOSTNAME, sHostName), sHostName == _T(""))
	{
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
		addrTo.sin_addr.S_un.S_addr = htonl(dwIP);
	}
	else
	{
		pHost = gethostbyname(T2A(sHostName));
		if (!pHost)
			return;

		addrTo.sin_addr.S_un.S_addr = *((DWORD*)pHost->h_addr_list[0]);
	}

	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6000);

	//这里面也有个特殊处理，CT2A不可以用，但是T2A可以用，不知为何
	//另外，因为传递的是字节，所有要用strlen计算字节数之后再加1
	GetDlgItemText(IDC_EDT_SEND, strSend);
	len = strSend.GetLength();	
	wsaBuf.buf = T2A(strSend);
	wsaBuf.len = len + 1;
	wsaBuf.len = strlen(wsaBuf.buf) + 1;

	SetDlgItemText(IDC_EDT_SEND, _T(""));
	if (SOCKET_ERROR == WSASendTo(m_socket, &wsaBuf, 1, &dwSend, 0,
		(SOCKADDR*)&addrTo, sizeof(SOCKADDR), NULL, NULL))
	{
		MessageBox(_T("发送数据失败！"));
		return;
	}
}
