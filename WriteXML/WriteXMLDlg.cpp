
// WriteXMLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WriteXML.h"
#include "WriteXMLDlg.h"

#import "msxml3.dll" 
using namespace MSXML2;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWriteXMLDlg 对话框




CWriteXMLDlg::CWriteXMLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteXMLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWriteXMLDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_WRITEXML, &CWriteXMLDlg::OnBnClickedBtnWritexml)
	ON_BN_CLICKED(IDC_BTN_WRITEINIT, &CWriteXMLDlg::OnBnClickedBtnWriteinit)
	ON_BN_CLICKED(IDC_BTN_READINI, &CWriteXMLDlg::OnBnClickedBtnReadini)
END_MESSAGE_MAP()


// CWriteXMLDlg 消息处理程序

BOOL CWriteXMLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWriteXMLDlg::OnPaint()
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
HCURSOR CWriteXMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWriteXMLDlg::OnBnClickedBtnWritexml()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("HELLO,XIAOHUO"));

	CString sDirect=_T("正向");
	CString sPath=_T("E:\\hehe.xml");


	::CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr xDoc;
	HRESULT hR=xDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hR))
		return;

	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProc = NULL;
	pXMLProc=xDoc->createProcessingInstruction(_T("xml"),_T("version=\"1.0\" encoding=\"GB2312\""));

	_variant_t vNullVal;
	vNullVal.vt = VT_NULL;
	xDoc->insertBefore(pXMLProc, vNullVal);

	//创建根节点
	MSXML2::IXMLDOMElementPtr pXMLRoot=NULL;
	pXMLRoot=xDoc->createElement(_T("TDimLocDlgSetting"));
	pXMLRoot->setAttribute(_T("Name"),_T("定位标注配置"));
	//添加根节点
	xDoc->appendChild(pXMLRoot);

	//创建下级元素节点
	MSXML2::IXMLDOMElementPtr pXMLEle=NULL;
	pXMLEle=xDoc->createElement(_T("DimDirection"));
	pXMLEle->setAttribute(_T("Direct"),(_variant_t)_T("x向"));
	pXMLRoot->appendChild(pXMLEle);

	xDoc->save((_variant_t)sPath);

	pXMLRoot.Release();
	xDoc.Release();
	::CoUninitialize();
}


//void OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	char tServerip[MAX_PATH] = { 0 };
//	DWORD dret = GetPrivateProfileString(_T("serverinfo"), _T("addr"), _T("du cuo le"), tServerip, 50, _T("D:\\VSProject\\ConfigurationFile\\Release\\config.ini"));
//	m_serverip = tServerip;
//	m_port = GetPrivateProfileInt(_T("serverinfo"), _T("port"), -1, _T("D:\\VSProject\\ConfigurationFile\\Release\\config.ini"));
//
//	CFile   file1("D:\\VSProject\\ConfigurationFile\\Release\\config.ini ", CFile::modeRead);
//	char   *pBuf;
//	int   iLen = file1.GetLength();
//	pBuf = new   char[iLen + 1];
//	file1.Read(pBuf, iLen);
//	pBuf[iLen] = 0;
//	file1.Close();
//	SetDlgItemText(IDC_EDIT_TEST, pBuf);
//}


void CWriteXMLDlg::OnBnClickedBtnWriteinit()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL Bw1 = WritePrivateProfileString(_T("serverinfo"), _T("addr"), _T("192.168.0.2"), _T("D:\\config.ini"));
	BOOL Bw2 = WritePrivateProfileString(_T("serverinfo"), _T("port"), _T("81"), _T("D:\\config.ini"));
	BOOL bW3=WritePrivateProfileString(_T("hello"), _T("port"), _T("81"), _T("D:\\config.ini"));
	if (!Bw2)
		::MessageBox(NULL,_T("写入失败"),_T("失败"),0);
	else
		::MessageBox(NULL,_T("写入成功"),_T("成功"),0);
}

void CWriteXMLDlg::OnBnClickedBtnReadini()
{
	CString str;
	DWORD dret = GetPrivateProfileString(_T("serverinfo"), _T("addr"), _T("du cuo le"), str.GetBuffer(512), 50, _T("D:\\config.ini"));
	str.ReleaseBuffer();
	int m = GetPrivateProfileInt(_T("serverinfo"), _T("port"), -1, _T("D:\\config.ini"));
}



HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void :OnTest() 
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	pList->DeleteAllItems();

	TCHAR szKey[1024] = {0};
	CString strKey = _T("");
	CString strKeyName = _T("");
	CString strKeyValue = _T("");

	TCHAR szBuffer[65536] = {0};

	CString strSectionName = _T("");
	GetDlgItemText(IDC_TEXT, strSectionName);

	//获得INI文件指定段的全部键名和键值
	int nBufferSize = GetPrivateProfileSection(strSectionName, szBuffer, 
		65536, m_strFileName);

	int nItem = 0;
	for (int n = 0, i = 0; n < nBufferSize; n++)
	{
		if (szBuffer[n] == 0)
		{
			szKey[i] = 0;
			strKey = szKey;
			strKeyName = strKey.Left(strKey.Find('='));
			strKeyValue = strKey.Mid(strKey.Find('=') + 1);
			pList->InsertItem(nItem, strKeyName);
			pList->SetItemText(nItem, 1, strKeyValue);
			i = 0;
			nItem++;
		}
		else
		{
			szKey[i] = szBuffer[n];
			i++;
		}
	}
}
