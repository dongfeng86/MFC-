
// GetAllWordInstancesDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "framework.h"
#include "GetAllWordInstances.h"
#include "GetAllWordInstancesDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <vector>
#include "CWordWindow.h"
#include "CWordSelection.h"
#include "CWordApplication.h"
#include "CWordParagraphs.h"
#include "CWordParagraph.h"
#include "CWordRange.h"
#include "CWordDocuments.h"
#include "CWordDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGetAllWordInstancesDlg 对话框



CGetAllWordInstancesDlg::CGetAllWordInstancesDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GETALLWORDINSTANCES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetAllWordInstancesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndLstProcess);
	DDX_Control(pDX, IDC_EDIT1, m_wndEdt);
}

BEGIN_MESSAGE_MAP(CGetAllWordInstancesDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGetAllWordInstancesDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CGetAllWordInstancesDlg::OnNMClickList1)
END_MESSAGE_MAP()


// CGetAllWordInstancesDlg 消息处理程序

BOOL CGetAllWordInstancesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	CRect rect;
	m_wndLstProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_wndLstProcess.GetClientRect(rect);
	m_wndLstProcess.InsertColumn(0, _T("序号"), LVCFMT_LEFT,rect.Width()/6.0);
	m_wndLstProcess.InsertColumn(2, _T("窗口标题"), LVCFMT_LEFT, rect.Width() * 5 / 6.0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetAllWordInstancesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetAllWordInstancesDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetAllWordInstancesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct EnumHWndsArg
{
	std::vector<HWND> *vecHWnds;
	DWORD dwProcessId;
}EnumHWndsArg, *LPEnumHWndsArg;

//根据进程名拿到进程id
DWORD GetProcessIDByName(CString strName, std::vector<DWORD> &vtcUid)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
	{
		CString strTemp = pe.szExeFile;
		if (strTemp == strName)
			vtcUid.push_back(pe.th32ProcessID);
	}
	CloseHandle(hSnapshot);
	return 0;
}

//获取当前进程id相关的hwnd
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	EnumHWndsArg *pArg = (LPEnumHWndsArg)lParam;
	if (pArg)
	{
		DWORD  idPprocess = 0;
		::GetWindowThreadProcessId(hwnd, &idPprocess);
		if (idPprocess == pArg->dwProcessId)
			pArg->vecHWnds->push_back(hwnd);
	}

	return TRUE;
}

//获取一个进程下所有的窗口
void GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds)
{
	EnumHWndsArg infoWin;
	infoWin.dwProcessId = processID;
	infoWin.vecHWnds = &vecHWnds;
	::EnumWindows(lpEnumFunc, (LPARAM)&infoWin);
}

//根据窗口句柄获取窗口信息
void GetWindowInfo(HWND hWnd, SWinInfo& cWndInfo)
{
	cWndInfo.hWnd = hWnd;
	cWndInfo.hParent = GetParent(hWnd);
	cWndInfo.hOwner = GetWindow(hWnd, GW_OWNER);
	cWndInfo.lStyle = GetWindowLong(hWnd, GWL_STYLE);
	::GetWindowText(hWnd, cWndInfo.pszTitle, MAXTITLELEN);
	::GetClassName(hWnd, cWndInfo.pszWinClass, MAXCLASSLEN);
	cWndInfo.idThread = ::GetWindowThreadProcessId(hWnd, &cWndInfo.idProcess);
}

//判断一个窗口是否为主窗口
bool IsMainWindow(HWND hWnd)
{
	if (!::IsWindow(hWnd))
		return false;

	SWinInfo cWndInfo;
	GetWindowInfo(hWnd, cWndInfo);
	DWORD dwVisibleStyle = WS_VISIBLE;
	bool bRet = _tcslen(cWndInfo.pszTitle)
		&& (cWndInfo.lStyle & dwVisibleStyle)
		&& !cWndInfo.hOwner;
	return bRet;
}

BOOL CALLBACK NextExcelChildWindow(HWND hWnd, LPARAM lParam)
{
	SWinInfo* pWinInfo = (SWinInfo*)lParam;
	TCHAR psz[MAXCLASSLEN] = { 0 };
	::GetClassName(hWnd, psz, MAXCLASSLEN);
	if (_tcscmp(psz, _T("EXCEL7")) == 0)
	{
		GetWindowInfo(hWnd, *pWinInfo);
		return FALSE;
	}
	return TRUE;

}

//根据主窗口的句柄得到EXCEL的COM对象
LPDISPATCH ExcelComFromMainWindowHandle(HWND hMainWin)
{
	SWinInfo cWinInfo;
	::EnumChildWindows(hMainWin, NextExcelChildWindow, (LPARAM)&cWinInfo);
	if (_tcscmp(cWinInfo.pszWinClass, _T("EXCEL7")) == 0)
	{
		void* pVoid = NULL;
		if (S_OK == AccessibleObjectFromWindow(cWinInfo.hWnd, OBJID_NATIVEOM, IID_IDispatch, &pVoid))
			return (LPDISPATCH)pVoid;
	}
	return NULL;
}

//获取Word的窗口COM对象
BOOL CALLBACK NextWordChildWindow(HWND hWnd, LPARAM lParam)
{
	SWinInfo* pWinInfo = (SWinInfo*)lParam;
	TCHAR psz[MAXCLASSLEN] = { 0 };
	::GetClassName(hWnd, psz, MAXCLASSLEN);
	if (_tcscmp(psz, _T("_WwG")) == 0) //word文档窗口的窗口类名称为"_WwG"
	{
		GetWindowInfo(hWnd, *pWinInfo);
		return FALSE;
	}
	return TRUE;
}

//根据主窗口的句柄得到Word的窗口COM对象
LPDISPATCH WordComFromMainWindowHandle(HWND hMainWin, SWinInfo& cWinInfo)
{
	cWinInfo.Reset();
	::EnumChildWindows(hMainWin, NextWordChildWindow, (LPARAM)&cWinInfo);
	if (_tcscmp(cWinInfo.pszWinClass, _T("_WwG")) == 0)
	{
		void* pVoid = NULL;
		if (S_OK == AccessibleObjectFromWindow(cWinInfo.hWnd, OBJID_NATIVEOM, IID_IDispatch, &pVoid))
			return (LPDISPATCH)pVoid;
	}
	return NULL;
}

void CGetAllWordInstancesDlg::OnBnClickedButton1()
{
	GetDocsCont(m_mapProcessId2String);
	m_wndLstProcess.DeleteAllItems();
	mapIter it;
	CString str;
	int iItem = 0;
	for (it = m_mapProcessId2String.begin(); it != m_mapProcessId2String.end(); it++)
	{
		str.Format(_T("%d"), iItem +1);
		m_wndLstProcess.InsertItem(iItem, str);
		m_wndLstProcess.SetItemText(iItem, 1, it->first);
		iItem++;
	}
}

void CGetAllWordInstancesDlg::GetDocsCont(MapDocTitle2Cont& mapProcessId2String)
{
	m_mapProcessId2String.clear();
	std::vector<DWORD> aridProcess;
	GetProcessIDByName(_T("WINWORD.EXE"), aridProcess);	//获取WORD进程
	for (int i = 0; i < aridProcess.size(); i++)
	{
		DWORD idProcess = aridProcess[i];
		std::vector<HWND> vtHWnds;
		GetHWndsByProcessID(idProcess, vtHWnds);	//取出该进程中所有对话框
		HWND hMainWin;
		for (int i = 0; i < vtHWnds.size(); i++)
		{
			hMainWin = vtHWnds[i];
			if (IsMainWindow(hMainWin))
			{
				LPDISPATCH pDispatch = NULL;
				SWinInfo cWinInfo;
				pDispatch = (LPDISPATCH)WordComFromMainWindowHandle(hMainWin, cWinInfo);
				if (pDispatch)
				{
					LPDISPATCH pWordDisp = NULL;
					CWordWindow wordMainWin;
					wordMainWin.AttachDispatch(pDispatch);
					pWordDisp = wordMainWin.get_Application();
					wordMainWin.DetachDispatch();

					CWordApplication wordApp;
					wordApp.AttachDispatch(pWordDisp);
					CWordDocuments wordDocs = wordApp.get_Documents();
					CString sContent;
					for (int i = 1; i < wordDocs.get_Count() + 1; i++)
					{
						sContent.Empty();
						VARIANT vt;
						vt.vt = VT_I4;
						vt.lVal = i;
						CWordDocument doc = wordDocs.Item(&vt);
						CString sTitle = doc.get_FullName();
						CWordParagraphs paragraphs = doc.get_Paragraphs();
						for (int i = 1; i < paragraphs.get_Count() + 1; i++)
						{
							CWordParagraph paragraph = paragraphs.Item(i);
							CWordRange range = paragraph.get_Range();
							sContent += range.get_Text();
						}
						sContent.Replace(_T("\r"), _T("\r\n"));
						m_mapProcessId2String[sTitle] = sContent;
					}
				}
				break;
			}
		}
	}
}

void CGetAllWordInstancesDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	//进行单击检测，这个结构已经被扩展为能够适应子项的单击检测。
	int iCurRow;
	LVHITTESTINFO cHitTest;
	cHitTest.pt = pNMItemActivate->ptAction;
	if (-1 !=m_wndLstProcess.SubItemHitTest(&cHitTest))	//检测给定坐标位于哪个单元格上
	{
		if (cHitTest.flags & LVHT_ONITEMLABEL)
		{
			iCurRow = cHitTest.iItem;
			CString sWinHandle = m_wndLstProcess.GetItemText(iCurRow, 1);
			if (m_mapProcessId2String.end() != m_mapProcessId2String.find(sWinHandle))
			{
				CString sCont = m_mapProcessId2String[sWinHandle];
				m_wndEdt.SetWindowText(sCont);
			}
		}
	}

	*pResult = 0;
}
