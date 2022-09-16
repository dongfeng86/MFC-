
// TreeCtrlExampleDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TreeCtrlExample.h"
#include "TreeCtrlExampleDlg.h"
#include "afxdialogex.h"
#include <vector>

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


// CTreeCtrlExampleDlg 对话框



CTreeCtrlExampleDlg::CTreeCtrlExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TREECTRLEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_wndTree);
}

BEGIN_MESSAGE_MAP(CTreeCtrlExampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CTreeCtrlExampleDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE1, &CTreeCtrlExampleDlg::OnNMCustomdrawTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTreeCtrlExampleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreeCtrlExampleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTreeCtrlExampleDlg 消息处理程序

#define XXX _T("HELLO")
#define CATXXX(x,y) x#y

//BOOL SplitString(const CString& str, std::vector<CString>& arSubStr, const CString& sSeparators=_T(' '))
//{
//	arSubStr.clear();
//	CString strEntire = str;
//	strEntire.Trim();
//	if (strEntire.IsEmpty())
//		return FALSE;
//
//	if (sSeparators.IsEmpty())
//	{
//		arSubStr.push_back(strEntire);
//		return TRUE;
//	}
//
//	CString strSub;
//	int iIndx;
//	while (!strEntire.IsEmpty())
//	{
//		if (-1 != (iIndx = strEntire.Find(sSeparators)))
//		{
//			strSub = strEntire.Left(iIndx).Trim();
//			if (!strSub.IsEmpty())
//				arSubStr.push_back(strSub);
//			strEntire.Delete(0, iIndx + sSeparators.GetLength());
//		}
//		else
//		{
//			arSubStr.push_back(strEntire);
//			break;
//		}
//	}
//
//	return TRUE;
//}

BOOL CTreeCtrlExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str111 = CATXXX(XXX, 2);
	CString str222= CATXXX(XXX, XXX);

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

	HICON icon[3];
	icon[0] = AfxGetApp()->LoadIconW(IDI_ICON1);
	icon[1] = AfxGetApp()->LoadIconW(IDI_ICON2);
	icon[2] = AfxGetApp()->LoadIconW(IDI_ICON3);

	//CImageList m_imageList; //图像列表

	//图像列表，程序完毕不能释放， 创建
	//30, 30: 图片的宽度和高度
	//ILC_COLOR32：样式
	// 3, 3： 有多少图片写多少
	m_imageList.Create(16, 16, ILC_COLOR32, 3, 3);

	//给图像列表添加图片
	for (int i = 0; i < 3; i++)
	{
		//图片列表加载图标
		m_imageList.Add(icon[i]);
	}


	//树控件设置图片列表
	DWORD dwStyles = GetWindowLongPtr(m_wndTree.m_hWnd, GWL_STYLE);//获取树控制原风格
	dwStyles |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_CHECKBOXES;
	SetWindowLongPtr(m_wndTree.m_hWnd, GWL_STYLE, dwStyles);//设置风格
	m_wndTree.SetImageList(&m_imageList, TVSIL_NORMAL);

	//给树创建节点
	//根节点，父节点，子节点
	//HTREEITEM root = m_wndTree.InsertItem(TEXT("中国"), 0, 0, NULL);
	//HTREEITEM fathter = m_wndTree.InsertItem(TEXT("北京"), 1, 1, root);
	//HTREEITEM son = m_wndTree.InsertItem(TEXT("海淀"), 2, 2, fathter);
	//HTREEITEM father2 = m_wndTree.InsertItem(TEXT("海南"), 1, 1, root);
	//HTREEITEM son2 = m_wndTree.InsertItem(TEXT("三亚"), 2, 2, father2);
	HTREEITEM root = m_wndTree.InsertItem(TEXT("中国"), 0, 0, NULL);
	HTREEITEM fathter = m_wndTree.InsertItem(TEXT("北京"), 1, 1, root);
	HTREEITEM son = m_wndTree.InsertItem(TEXT("海淀"), 2, 2, fathter);
	HTREEITEM father2 = m_wndTree.InsertItem(TEXT("海南"), 1, 1, root);
	HTREEITEM son2 = m_wndTree.InsertItem(TEXT("三亚"), 2, 2, father2);

	m_wndTree.SetItemState(fathter, INDEXTOOVERLAYMASK(2), TVIS_OVERLAYMASK);

	TCHAR ch1[256];
	TCHAR ch2[256];
	TCHAR ch3[256];
	CString str = _T("and roid-ip hone-wp7");
	/*字符串取道'-'为止,后面还需要跟着分隔符'-',起到过滤作用,有点类似于第7点*/
	//_stscanf(str, _T("%[^-]-%[^-]-%[^-]"), ch1, ch2, ch3);

	CString strNew = _T(',');

	CString strNew2;
	strNew2 = _T('x');

	CString strNew3(_T(','));

	//设置某个节点被选中
//	m_wndTree.SelectItem(fathter);	  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTreeCtrlExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeCtrlExampleDlg::OnPaint()
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
HCURSOR CTreeCtrlExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreeCtrlExampleDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}



//CImageList Cil1, Cil2;//大小图标像列表

//BOOL CVCTREEDlg::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//	.....//原来其它代码
//	// TODO: Add extra initialization here
//	// 此处开始增加代码
//		CVCTREEApp *pApp = (CVCTREEApp *)AfxGetApp();//创建图象列表
//	Cil1.Create(16, 16, ILC_COLOR, 2, 2);
//	Cil1.Add(pApp->LoadIcon(IDI_PM));
//	Cil1.Add(pApp->LoadIcon(IDI_CJ));
//	m_TreeCtrl.SetImageList(&Cil1, TVSIL_NORMAL); //设置图象列表
//	DWORD dwStyles = GetWindowLong(m_TreeCtrl.m_hWnd, GWL_STYLE);//获取树控制原风格
//	dwStyles |= TVS_EDITLABELS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
//	SetWindowLong(m_TreeCtrl.m_hWnd, GWL_STYLE, dwStyles);//设置风格
//	char * CJ[4] = { "玉溪卷烟厂","云南卷烟厂","沈阳卷烟厂","成都卷烟厂" };//根数据名称
//	char * PM[4][5] = {
//	{"红梅一","红梅二","红梅三","红梅四","红梅五"},//产品数据项
//	{"白梅一","白梅二","白梅三","白梅四","白梅五"},
//	{"绿梅一","绿梅二","绿梅三","绿梅四","绿梅五"},
//	{"青梅一","青梅二","青梅三","青梅四","青梅五"} };
//	int i, j;
//	HTREEITEM hRoot, hCur;//树控制项目句柄
//	TV_INSERTSTRUCT TCItem;//插入数据项数据结构
//	TCItem.hParent = TVI_ROOT;//增加根项
//	TCItem.hInsertAfter = TVI_LAST;//在最后项之后
//	TCItem.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;//设屏蔽
//	TCItem.item.pszText = "数据选择";
//	TCItem.item.lParam = 0;//序号
//	TCItem.item.iImage = 0;//正常图标
//	TCItem.item.iSelectedImage = 1;//选中时图标
//	hRoot = m_TreeCtrl.InsertItem(&TCItem);//返回根项句柄
//	for (i = 0; i < 4; i++) {//增加各厂家
//		TCItem.hParent = hRoot;
//		TCItem.item.pszText = CJ[i];
//		TCItem.item.lParam = (i + 1) * 10;//子项序号
//		hCur = m_TreeCtrl.InsertItem(&TCItem);
//		for (j = 0; j < 5; j++) {//增加各产品
//			TCItem.hParent = hCur;
//			TCItem.item.pszText = PM[i][j];
//			TCItem.item.lParam = (i + 1) * 10 + (j + 1);//子项序号
//			m_TreeCtrl.InsertItem(&TCItem);
//		}
//		m_TreeCtrl.Expand(hCur, TVE_EXPAND);//展开树
//	}
//	m_TreeCtrl.Expand(hRoot, TVE_EXPAND);//展开上一级树
//	return TRUE; // return TRUE unless you set the focus to a control
//}

//m_listFile为树状控件变量，pszDirName为初始目录路径名，parent为树状控件根节点

//void CreateList(HTREEITEM parent, char pszDirName[])
//{
//	CFileFind file;
//	BOOL bRet;
//	char tempFileName[200];
//	sprintf(tempFileName, "%s\\*.*", pszDirName);
//
//	bRet = file.FindFile(tempFileName);
//
//
//	while (bRet)
//	{
//		char tempFileName1[200];
//		bRet = file.FindNextFile();
//		if (!file.IsDots())
//		{
//			sprintf(tempFileName1, "%s", file.GetFileName());
//
//			if (file.IsDirectory())
//			{
//				char tempDirName[200];
//				sprintf(tempDirName, "%s\\%s", pszDirName, tempFileName1);
//				HTREEITEM itemParent = m_listFile.InsertItem(file.GetFileName(), 0, 0, parent);
//
//				CreateList(itemParent, tempDirName);
//			}
//			else
//			{
//				m_listFile.InsertItem(file.GetFileName(), 1, 1, parent);
//			}
//		}
//	}
//	file.Close();
//
//}

void sdfasda()
{
	double f1 = 10, f2 = 10;
	if (fabs(f1 - f2) <= FLT_EPSILON)			//比较两个浮点数是否相等
	{
		//...
	}
	if (f1>f2 && fabs(f1 - f2) > FLT_EPSILON)	//比较一个浮点数是否大于另一个
	{
		//...
	}
	if (f1<f2 && fabs(f1 - f2) > FLT_EPSILON)		//比较一个浮点数是否小于另一个
	{
		//...
	}
}


void CTreeCtrlExampleDlg::OnNMCustomdrawTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMTVCUSTOMDRAW *ptvTreeCtrl = (NMTVCUSTOMDRAW *)pNMHDR;

	if (ptvTreeCtrl->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	else if (ptvTreeCtrl->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		//自定义绘制  
		CRect rect;
		rect = ptvTreeCtrl->nmcd.rc;

		*pResult = CDRF_DODEFAULT;
		return;
	}


	*pResult = 0;
}

//
//CMutiTreeCtrl::CMutiTreeCtrl()
//{
//	m_uFlags = 0;
//}
//void CMutiTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	HTREEITEM hItem = HitTest(point, &m_uFlags);
//	if ((m_uFlags&TVHT_ONITEMSTATEICON))//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择
//	{
//		UINT nState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;
//		nState = (nState == 3) ? 1 : 3;
//		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);
//	}
//	CTreeCtrl::OnLButtonDown(nFlags, point);
//}

void CTreeCtrlExampleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("单击了默认按钮"));
}


void CTreeCtrlExampleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTreeCtrlExampleDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	MessageBox(_T("单击了IDOK"));
	CDialog::OnOK();
}
