
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
	MessageBox(_T("HELLO,XIAOHUO"));

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

	xDoc->save((_variant_t)sPath);

	pXMLRoot.Release();
	xDoc.Release();
	::CoUninitialize();
}


//void OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//���INI�ļ�ָ���ε�ȫ�������ͼ�ֵ
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
