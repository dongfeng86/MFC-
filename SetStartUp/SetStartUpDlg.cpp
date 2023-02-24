
// SetStartUpDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SetStartUp.h"
#include "SetStartUpDlg.h"
#include "afxdialogex.h"
#include <afxdlgs.h>
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


// CSetStartUpDlg 对话框



CSetStartUpDlg::CSetStartUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETSTARTUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSetStartUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_STARTUP_ITEM, m_wndLst);
}

BEGIN_MESSAGE_MAP(CSetStartUpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SHOW, &CSetStartUpDlg::OnBnClickedBtnShow)
	ON_BN_CLICKED(IDC_BTN_DEL_ITEM, &CSetStartUpDlg::OnBnClickedBtnDelItem)
	ON_BN_CLICKED(IDC_BTN_ADD_STARTUP, &CSetStartUpDlg::OnBnClickedBtnAddStartup)
END_MESSAGE_MAP()


// CSetStartUpDlg 消息处理程序

void CSetStartUpDlg::FillList()
{
	CString sAppName;
	m_wndLst.DeleteAllItems();
	for (int i = 0; i < m_arsStartItemPath.size(); i++)
	{
		m_wndLst.InsertItem(i, m_arsStart[i]);
		m_wndLst.SetItemText(i, 1, m_arsStartItemPath[i]);
	}
}

BOOL CSetStartUpDlg::OnInitDialog()
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
	m_wndLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;
	m_wndLst.GetClientRect(rect);
	m_wndLst.InsertColumn(0, _T("程序名"), LVCFMT_LEFT, rect.Width() / 3.0, 0);
	m_wndLst.InsertColumn(1, _T("安装路径"), LVCFMT_LEFT, rect.Width()*2.0 / 3.0, 1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSetStartUpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSetStartUpDlg::OnPaint()
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
HCURSOR CSetStartUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

//获取一个注册表键下面的各个子键名称，以及改键下面所有值名称
void QueryKey(HKEY hKey,std::vector<CString>* parSubKey,std::vector<CString>* parKeyValueName)
{
	TCHAR    pszSubKeyName[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    pszClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

	TCHAR  pszValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		pszClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	// Enumerate the subkeys, until RegEnumKeyEx fails.
	if (parSubKey)
	{
		for (i = 0; i < cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i, pszSubKeyName, &cbName,
				NULL, NULL, NULL, &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
				parSubKey->push_back(pszSubKeyName);
		}
	}

	// Enumerate the key values. 
	if (parKeyValueName)
	{
		for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
		{
			cchValue = MAX_VALUE_NAME;
			pszValue[0] = _T('\0');
			retCode = RegEnumValue(hKey, i, pszValue, &cchValue,
				NULL, NULL, NULL, NULL);

			if (retCode == ERROR_SUCCESS)
				parKeyValueName->push_back(pszValue);
		}
	}
}

CString CSetStartUpDlg::m_sPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

void CSetStartUpDlg::OnBnClickedBtnShow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_arsStartItemPath.clear();
	m_arsStart.clear();
	
	HKEY hRegKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, m_sPath, NULL, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY, &hRegKey))
		return;

#define _MAX_VALUE_BUF_	2048
	TCHAR  pszValueName[MAX_VALUE_NAME];
	DWORD cchValueName = MAX_VALUE_NAME;
	BYTE pszValue[_MAX_VALUE_BUF_] = {0};
	DWORD dwBufSize = _MAX_VALUE_BUF_;
	int i = 0;
	long lRetCode;
	DWORD dwType;
	while (ERROR_NO_MORE_ITEMS != 
		(lRetCode = RegEnumValue(hRegKey, i++, pszValueName, &cchValueName, NULL, &dwType, pszValue, &dwBufSize)))
	{
		if (ERROR_SUCCESS == lRetCode)
		{
			if (dwType == REG_SZ)
			{
				pszValue[dwBufSize] = '\0';
				m_arsStartItemPath.push_back((TCHAR*)pszValue);
				m_arsStart.push_back(pszValueName);
			}
		}
		dwBufSize = _MAX_VALUE_BUF_;
		cchValueName = MAX_VALUE_NAME;
	}

	RegCloseKey(hRegKey);
	FillList();
}


void CSetStartUpDlg::OnBnClickedBtnDelItem()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hRegKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, m_sPath, NULL, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY, &hRegKey))
		return;
	int iSelect = m_wndLst.GetNextItem(-1, LVIS_SELECTED);
	if (-1 != iSelect)
	{
		CString sKeyName = m_wndLst.GetItemText(iSelect, 0);
		m_wndLst.DeleteItem(iSelect);
		RegDeleteValue(hRegKey, sKeyName);

	}
	RegCloseKey(hRegKey);
}


void CSetStartUpDlg::OnBnClickedBtnAddStartup()
{
	// szFilters is a text string that includes two file name filters:
	TCHAR szFilters[] = _T("可执行文件 (*.exe)|*.exe|All Files (*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDlg.DoModal() == IDOK)
	{
		CString sPath = fileDlg.GetPathName();

		//将用户选择的文件放到启动项中
		//打开注册表
		HKEY hRegKey;
		if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, m_sPath, NULL, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY, &hRegKey))
			return;
		CString sAppName = sPath.Mid(sPath.ReverseFind(_T('\\')) + 1);
		if (ERROR_SUCCESS == RegSetValueEx(hRegKey, sAppName, NULL, REG_SZ,
			(const BYTE*)sPath.GetString(), (sPath.GetLength() + 1) * sizeof(TCHAR)))
		{
			int iNew = m_wndLst.InsertItem(m_wndLst.GetItemCount(), sAppName);
			m_wndLst.SetItemText(iNew, 1, sPath);
		}

		RegCloseKey(hRegKey);
	}
}
