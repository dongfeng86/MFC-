
// FindFileInDirDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindFileInDir.h"
#include "FindFileInDirDlg.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFindFileInDirDlg �Ի���




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


// CFindFileInDirDlg ��Ϣ�������

BOOL CFindFileInDirDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFindFileInDirDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFindFileInDirDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//---------------------------------------------
//=Function Name:   FindFinleInDir
//=Description:  	���ض�Ŀ¼�²����ļ�
//=Parameter:       pszFileName Ҫ���ҵ��ļ���
//=Parameter:       pszDir Ҫ���ĸ�Ŀ¼�²���
//=Parameter:       arFindResult ���ҵĽ���������������
//=Parameter:       int iRecursionCount �ݹ���ҵ���ȣ�0�����ڵ�ǰĿ¼�²��ң�����0����ݹ���ȣ�-1����ݹ鵽���һ�㡣
//---------------------------------------------
void FindFinleInDir(const TCHAR* pszFileName,const TCHAR* pszDir,std::vector<CString>& arFindResult,int iRecursionCount)
{
	if(_tcscmp(pszFileName,_T(""))==0)	//���Ҫ���ҵ��ļ���Ϊ�գ�ֱ�ӷ���
		return;

	CString sWildcard(pszDir);
	if(sWildcard.Right(1)!=_T("\\"))
		sWildcard+=_T("\\");		//��֤Ŀ¼��'\'��β
	sWildcard+=_T("*.*");			//����ͨ���

	CFileFind cFinder;
	BOOL bWorking = cFinder.FindFile(sWildcard);	//����һ������
	while(bWorking)
	{
		bWorking = cFinder.FindNextFile();

		if(cFinder.IsDots())			//�����'.'����'..'
			continue;
		else if(cFinder.IsDirectory())	//�����һ����Ŀ¼
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

	cFinder.Close();		//�رղ���
}

//---------------------------------------------
//=Function Name:   WildcardSearch
//=Description:  	֧�����ض�Ŀ¼�µݹ����ĳ���ļ����ļ���֧��ͨ���
//=Parameter:       pszFileName Ҫ���ҵ��ļ���
//=Parameter:       pszDir Ҫ���ĸ�Ŀ¼�²���
//=Parameter:       arFindResult ���ҵĽ���������������
//=Parameter:       int iRecursionCount �ݹ���ҵ���ȣ�0�����ڵ�ǰĿ¼�²��ң�����0����ݹ���ȣ�-1����ݹ鵽���һ�㡣
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
	iDotPos = sFileName.ReverseFind(_T('.'));	//�Ƿ��ļ���չ��
	if (0 <= iDotPos)
	{
		//��չ��ǰ����"*"
		if (iDotPos > 0)
		{
			if (_T('*') != sFileName[iDotPos - 1] && _T('?') != sFileName[iDotPos - 1])
				sFileName.Insert(iDotPos, _T('*'));
		}
		else
			sFileName.Insert(iDotPos, _T('*'));

		//�����չ�����һλ����*����?������*
		if (_T('*') != sFileName[sFileName.GetLength() - 1] && _T('?') != sFileName[sFileName.GetLength() - 1])
			sFileName.Insert(sFileName.GetLength(), _T('*'));
	}
	else
		sFileName += _T('*');
	sWildcarFullpath += sFileName;

	//����������ǰ�ļ����µ������ļ�
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

	//�ݹ�������ǰ�ļ����µ�������Ŀ¼
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
	//FindFinleInDir(_T("arxdev.chm"),_T("E:\\������Ŀ\\arx\\"),arFind,-1);
	WildcardSearch(_T("cn"), _T("C:\\Users\\Administrator\\Desktop\\download"), arFind, -1);
	
	OnOK();
}
