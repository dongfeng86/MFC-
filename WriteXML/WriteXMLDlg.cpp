
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
	ON_BN_CLICKED(IDC_BTN_READXML, &CWriteXMLDlg::OnBnClickedBtnReadxml)
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

	//继续创建下级元素
	MSXML2::IXMLDOMElementPtr pXMLEle2 = NULL;
	for (int i = 0; i < 6; i++)
	{
		pXMLEle2 = NULL;
		CString sNodeName;
		sNodeName.Format(_T("第%d个元素"), i);
		pXMLEle2 = xDoc->createElement((_bstr_t)sNodeName);
		CString sss;
		sss.Format(_T("内容为:%d"), i);
		pXMLEle2->put_text((_bstr_t)sss);
		pXMLRoot->appendChild(pXMLEle2);
	}


	xDoc->save((_variant_t)sPath);

	pXMLRoot.Release();
	xDoc.Release();
	::CoUninitialize();
}

void CWriteXMLDlg::OnBnClickedBtnReadxml()
{
	CString XMLFilePath = _T("E:\\hehe.xml");

	MSXML2::IXMLDOMDocumentPtr xdoc;	//定义IXMLDOMDocumentPtr接口对象
	xdoc.CreateInstance(__uuidof(MSXML2::DOMDocument));	//实例化对象
	xdoc->load((_bstr_t)XMLFilePath);	//加载xml文件
	MSXML2::IXMLDOMNodeListPtr nodelist = NULL;
	MSXML2::IXMLDOMNodeListPtr subItems = NULL;
	nodelist = xdoc->selectNodes(_T("TDimLocDlgSetting"));

	MSXML2::IXMLDOMNodePtr Root;
	MSXML2::IXMLDOMNodePtr node;

	Root = nodelist->nextNode();
	_bstr_t bstrname = Root->nodeName;
	subItems = Root->childNodes;

	CString sNodeName;
	CString sNodeValue;
	for (int i = 0; i < subItems->length; i++)
	{
		node = subItems->nextNode();
		_bstr_t rowname = node->nodeName;
		_bstr_t value=node->Gettext();
	}
}


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

