
// FindFileInDirDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FindFileInDir.h"
#include "FindFileInDirDlg.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFindFileInDirDlg 对话框




CFindFileInDirDlg::CFindFileInDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindFileInDirDlg::IDD, pParent)
	, m_sInputFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindFileInDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_sInputFileName);
}

BEGIN_MESSAGE_MAP(CFindFileInDirDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_FILENAME, &CFindFileInDirDlg::OnEnChangeEditFilename)
	ON_BN_CLICKED(IDOK, &CFindFileInDirDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFindFileInDirDlg 消息处理程序

BOOL CFindFileInDirDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFindFileInDirDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFindFileInDirDlg::OnPaint()
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
HCURSOR CFindFileInDirDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//---------------------------------------------
//=Function Name:   FindFinleInDir
//=Description:  	在特定目录下查找文件
//=Parameter:       pszFileName 要查找的文件名
//=Parameter:       pszDir 要在哪个目录下查找
//=Parameter:       arFindResult 查找的结果保存在这个数组
//=Parameter:       int iRecursionCount 递归查找的深度，0代表在当前目录下查找；大于0代表递归深度；-1代表递归到最后一层。
//---------------------------------------------
void FindFinleInDir(const TCHAR* pszFileName,const TCHAR* pszDir,std::vector<CString>& arFindResult,int iRecursionCount)
{
	if(_tcscmp(pszFileName,_T(""))==0)	//如果要查找的文件名为空，直接返回
		return;

	CString sWildcard(pszDir);
	if(sWildcard.Right(1)!=_T("\\"))
		sWildcard+=_T("\\");		//保证目录以'\'结尾
	sWildcard+=_T("*.*");			//加上通配符

	CFileFind cFinder;
	BOOL bWorking = cFinder.FindFile(sWildcard);	//开启一个搜索
	while(bWorking)
	{
		bWorking = cFinder.FindNextFile();

		if(cFinder.IsDots())			//如果是'.'或者'..'
			continue;
		else if(cFinder.IsDirectory())	//如果是一个子目录
		{
			if(-1==iRecursionCount || iRecursionCount>0)
			{
				int iRecurse=iRecursionCount;
				if(iRecurse>0)
					iRecurse--;

				FindFinleInDir(pszFileName,cFinder.GetFilePath(),arFindResult,iRecurse);
			}
		}
		else
		{
			CString strrr=cFinder.GetFileName();
			if(pszFileName==cFinder.GetFileName())
				arFindResult.push_back(cFinder.GetFilePath());
		}
	}

	cFinder.Close();		//关闭查找
}

//---------------------------------------------
//=Function Name:   WildcardSearch
//=Description:  	支持在特定目录下递归查找某个文件，文件名支持通配符
//=Parameter:       pszFileName 要查找的文件名
//=Parameter:       pszDir 要在哪个目录下查找
//=Parameter:       arFindResult 查找的结果保存在这个数组
//=Parameter:       int iRecursionCount 递归查找的深度，0代表在当前目录下查找；大于0代表递归深度；-1代表递归到最后一层。
//---------------------------------------------
void WildcardSearch(const TCHAR* pszFileName, const TCHAR* pszDir, std::vector<CString>& arFindResult, int iRecursionCount)
{
	if (!_tcsicmp(pszFileName, _T("")) || !_tcsicmp(pszDir, _T("")))
		return;

	CString sWildcarFullpath(pszDir);
	if (sWildcarFullpath.Right(1) != _T("\\"))
		sWildcarFullpath += _T("\\");

	CString sFileName(pszFileName);
	int iDotPos = -1;
	iDotPos = sFileName.ReverseFind(_T('.'));	//是否含文件扩展名
	if (0 <= iDotPos)
	{
		//扩展名前加上"*"
		if (iDotPos > 0)
		{
			if (_T('*') != sFileName[iDotPos - 1] && _T('?') != sFileName[iDotPos - 1])
				sFileName.Insert(iDotPos, _T('*'));
		}
		else
			sFileName.Insert(iDotPos, _T('*'));

		//如果扩展名最后一位不是*或者?，加上*
		if (_T('*') != sFileName[sFileName.GetLength() - 1] && _T('?') != sFileName[sFileName.GetLength() - 1])
			sFileName.Insert(sFileName.GetLength(), _T('*'));
	}
	else
		sFileName += _T('*');
	sWildcarFullpath += sFileName;

	//首先搜索当前文件夹下的所有文件
	CFileFind finder;
	BOOL bWorking = finder.FindFile(sWildcarFullpath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDirectory() && !finder.IsDots() && !finder.IsHidden())
		{
			CString sFind;
			sFind = finder.GetFilePath();
			arFindResult.push_back(sFind);
		}
	}
	finder.Close();

	//递归搜索当前文件夹下的所有子目录
	sWildcarFullpath = pszDir;
	if (sWildcarFullpath.Right(1) != _T("\\"))
		sWildcarFullpath += _T("\\");
	sWildcarFullpath += _T("*.*");
	bWorking = finder.FindFile(sWildcarFullpath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDots())
			continue;
		else if (finder.IsDirectory())
		{
			if (-1 == iRecursionCount)
			{
				CString str = finder.GetFilePath();
				WildcardSearch(pszFileName, str, arFindResult, iRecursionCount);
			}
			else if (iRecursionCount > 0)
			{
				CString str = finder.GetFilePath();
				WildcardSearch(pszFileName, str, arFindResult, iRecursionCount - 1);
			}
		}
	}
	finder.Close();
}

void CFindFileInDirDlg::OnEnChangeEditFilename()
{
	UpdateData(TRUE);
}

void CFindFileInDirDlg::OnBnClickedOk()
{
	std::vector<CString> arFind;
	//FindFinleInDir(_T("arxdev.chm"),_T("E:\\程序项目\\arx\\"),arFind,-1);
	WildcardSearch(_T("cn"), _T("C:\\Users\\Administrator\\Desktop\\download"), arFind, -1);
	
	OnOK();
}
