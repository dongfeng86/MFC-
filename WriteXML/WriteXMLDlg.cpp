
// WriteXMLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WriteXML.h"
#include "WriteXMLDlg.h"

#import "msxml3.dll" 
using namespace MSXML2;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWriteXMLDlg �Ի���




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


// CWriteXMLDlg ��Ϣ�������

BOOL CWriteXMLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWriteXMLDlg::OnPaint()
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
HCURSOR CWriteXMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWriteXMLDlg::OnBnClickedBtnWritexml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sDirect=_T("����");
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

	//�������ڵ�
	MSXML2::IXMLDOMElementPtr pXMLRoot=NULL;
	pXMLRoot=xDoc->createElement(_T("TDimLocDlgSetting"));
	pXMLRoot->setAttribute(_T("Name"),_T("��λ��ע����"));
	//��Ӹ��ڵ�
	xDoc->appendChild(pXMLRoot);

	//�����¼�Ԫ�ؽڵ�
	MSXML2::IXMLDOMElementPtr pXMLEle=NULL;
	pXMLEle=xDoc->createElement(_T("DimDirection"));
	pXMLEle->setAttribute(_T("Direct"),(_variant_t)_T("x��"));
	pXMLRoot->appendChild(pXMLEle);

	//���������¼�Ԫ��
	MSXML2::IXMLDOMElementPtr pXMLEle2 = NULL;
	for (int i = 0; i < 6; i++)
	{
		pXMLEle2 = NULL;
		CString sNodeName;
		sNodeName.Format(_T("��%d��Ԫ��"), i);
		pXMLEle2 = xDoc->createElement((_bstr_t)sNodeName);
		CString sss;
		sss.Format(_T("����Ϊ:%d"), i);
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

	MSXML2::IXMLDOMDocumentPtr xdoc;	//����IXMLDOMDocumentPtr�ӿڶ���
	xdoc.CreateInstance(__uuidof(MSXML2::DOMDocument));	//ʵ��������
	xdoc->load((_bstr_t)XMLFilePath);	//����xml�ļ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL Bw1 = WritePrivateProfileString(_T("serverinfo"), _T("addr"), _T("192.168.0.2"), _T("D:\\config.ini"));
	BOOL Bw2 = WritePrivateProfileString(_T("serverinfo"), _T("port"), _T("81"), _T("D:\\config.ini"));
	BOOL bW3=WritePrivateProfileString(_T("hello"), _T("port"), _T("81"), _T("D:\\config.ini"));
	if (!Bw2)
		::MessageBox(NULL,_T("д��ʧ��"),_T("ʧ��"),0);
	else
		::MessageBox(NULL,_T("д��ɹ�"),_T("�ɹ�"),0);
}

void CWriteXMLDlg::OnBnClickedBtnReadini()
{
	CString str;
	DWORD dret = GetPrivateProfileString(_T("serverinfo"), _T("addr"), _T("du cuo le"), str.GetBuffer(512), 50, _T("D:\\config.ini"));
	str.ReleaseBuffer();
	int m = GetPrivateProfileInt(_T("serverinfo"), _T("port"), -1, _T("D:\\config.ini"));
}

