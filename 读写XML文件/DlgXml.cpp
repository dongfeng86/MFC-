// DlgXml.cpp : ʵ���ļ�
//

#include "stdafx.h"
#import "msxml3.dll" 
using namespace MSXML2;

#include "��дXML�ļ�.h"
#include "DlgXml.h"



// CDlgXml �Ի���

IMPLEMENT_DYNAMIC(CDlgXml, CDialog)

CDlgXml::CDlgXml(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXml::IDD, pParent)
	,m_fileProjectPath(_T("E:\\"))
{

}

CDlgXml::~CDlgXml()
{
}

void CDlgXml::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgXml, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CDlgXml::OnBnClickedBtnConnect)
END_MESSAGE_MAP()

//void CDlgXml::ReadXml(CString strXmlPath)
//{
//	MSXML2::IXMLDOMDocumentPtr pDoc;
//	::CoInitialize(NULL);
//	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30)); 
//
//	if (!SUCCEEDED(hr)) 
//	{  
//		MessageBox(_T("����DOMDocument����ʧ�ܡ�\n�������л���"), _T("����"), MB_ICONERROR); 
//		return;
//	}
//	// ��ȡxml
//	pDoc->put_async(VARIANT_FALSE);
//	VARIANT_BOOL bhr = pDoc->load((_variant_t)strXmlPath);
//
//	if (bhr != VARIANT_TRUE) {
//		MessageBox(_T("�޷���ȷ��ȡxml�ļ�"), _T("����"), MB_ICONERROR);
//		return;
//	}
//
//	// ���ڵ�ȡ��
//	MSXML2::IXMLDOMElementPtr root = pDoc->documentElement;
//	// ȡ�ø��ڵ������
//	_variant_t strRootName = root->nodeName;
//	_bstr_t wstrRootName(strRootName.bstrVal);
//	MSXML2::IXMLDOMNodeListPtr nodeList = root->GetchildNodes();//cases
//
//	// ����cases���ӽڵ�
//	ReadCase(nodeList);
//}

//void CDlgXml::ReadXml()
//{
//	::CoInitialize(NULL);
//	MSXML2::IXMLDOMElementPtr xRoot;  
//	MSXML2::IXMLDOMElementPtr xElement;  
//	MSXML2::IXMLDOMNodeListPtr xNodes; //ĳ���ڵ�������ֽڵ�  
//	MSXML2::IXMLDOMNamedNodeMapPtr xNodeAtts;//ĳ���ڵ����������;  
//	MSXML2::IXMLDOMNodePtr xNode;  
//	static MSXML2::IXMLDOMDocumentPtr xDoc;
//	HRESULT HR = xDoc.CreateInstance(_uuidof(MSXML2::DOMDocument30));  
//	if(!SUCCEEDED(HR))  
//	{  
//		return;  
//	}  
//	xDoc->load((_variant_t)m_fileProjectPath);
//	xRoot = xDoc->GetdocumentElement();//��ø��ڵ�;  
//	xRoot->get_childNodes(&xNodes);//��ø��ڵ�������ӽڵ�;  
//	long xNodesNum,AttsNum;
//	xNodes->get_length(&xNodesNum);//��������ӽڵ�ĸ���;  
//
//
//	for(int i = 0; i < xNodesNum; i++)  
//	{  
//		xNodes->get_item(i, &xNode);//���ĳ���ӽڵ�;  
//
//		CString  sBaseName = CString(((string)xNode->GetbaseName()).c_str());
//		xNode->get_attributes(&xNodeAtts);//���ĳ���ڵ����������;  
//		xNodeAtts->get_length(&AttsNum);//����������Եĸ���; 
//
//		if (_T("Project") == sBaseName)
//		{
//			HTREEITEM hRoot;
//			MSXML2::IXMLDOMNodePtr xNodeItem;
//			UINT sDialogId;
//			CString sDialogConfig;
//			CString sScene;
//			for(int j = 0; j < AttsNum; j++)  
//			{  
//				xNodeAtts->get_item(j, &xNodeItem);//���ĳ������;  
//				CString sName = (char*)(_bstr_t)xNodeItem->nodeName;
//				if (_T("Name") == sName)
//				{
//					CString sText = (char*)(_bstr_t)xNodeItem->text;
//					hRoot = m_wndTreProject.InsertItem(sText, 0);
//				}
//				else if (_T("Dialog") == sName)
//				{
//					sDialogId = _tstoi(CString((char*)xNodeItem->text));
//				}
//				else if (_T("DlgConfig") == sName)
//				{
//					sDialogConfig = (char*)(_bstr_t)xNodeItem->text;
//				}
//				else if (_T("Scene") == sName)
//				{
//					sScene = (char*)(_bstr_t)xNodeItem->text;
//				}
//			}
//			xNodeItem.Release();
//
//			if (0 != sDialogId)
//			{
//				StScene &scene = m_mapDlg[hRoot];
//				scene.iSceneId = sDialogId;
//				scene.sScene = sScene;
//				scene.pDlg = CreateSceneDlg(sDialogId, sScene);
//				SetDlgConfig(m_mapDlg.find(hRoot), sDialogConfig);
//			}
//
//			OpenProject(xNode, hRoot);
//		}
//	}
//
//
//	xNodes.Release();
//	xNode.Release();
//	xRoot.Release();
//	xDoc.Release();
//	::CoUninitialize();
//}

//void Write2222()
//{
//	::CoInitialize(NULL);MSXML2
//	MSXML2::IXMLDOMDocumentPtr xDoc;
//	HRESULT HR = xDoc.CreateInstance(_uuidof(MSXML2::DOMDocument30));  
//	if(!SUCCEEDED(HR))  
//	{  
//		return;
//	}  
//
//	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProc = NULL;
//	pXMLProc = xDoc->createProcessingInstruction("xml", "version='1.0' encoding='GB2312'");
//
//	_variant_t vNullVal;
//	vNullVal.vt = VT_NULL;
//	xDoc->insertBefore(pXMLProc, vNullVal);
//
//	// ���������
//	MSXML2::IXMLDOMElementPtr pXMLRoot= NULL; 
//	pXMLRoot = xDoc->createElement("SmokeControlConfig");
//	pXMLRoot->setAttribute("Name", "��������������");
//	// ��Ӹ����
//	xDoc->appendChild(pXMLRoot); 
//
//	// �����¼�Ԫ�ؽ��
//	MSXML2::IXMLDOMElementPtr pXMLEle = NULL;
//	pXMLEle = xDoc->createElement("Project");
//	pXMLEle->setAttribute("Name", (_variant_t)sRootText);
//	pXMLEle->setAttribute("Dialog", m_mapDlg[hRootItem].iSceneId);
//	pXMLEle->setAttribute("Scene", (_variant_t)m_mapDlg[hRootItem].sScene);
//	pXMLEle->setAttribute(_T("DlgConfig"), (_variant_t)GetDlgConfig(m_mapDlg[hRootItem].iSceneId, m_mapDlg[hRootItem].pDlg));
//	// ���Ԫ�ؽ��
//	pXMLRoot->appendChild(pXMLEle);
//
//	//SaveProject(pXMLEle, hRootItem, xDoc);
//
//	xDoc->save((_variant_t)m_fileProjectPath);
//	//XMLNode.Release();
//	pXMLRoot.Release();
//	xDoc.Release();
//	::CoUninitialize(); 
//}

void CDlgXml::WriteXml()
{
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
	pXMLEle->appendChild(pXMLEle);

	xDoc->save((_variant_t)sPath);

	pXMLRoot.Release();
	xDoc.Release();
	::CoUninitialize();
}


//void CDlgXml::ReadCase(MSXML2::IXMLDOMNodeListPtr nodeList)
//{
//	CString strLogInfo;
//	strLogInfo.Empty();
//	CString strNo;              // case���
//	CString strSrcFile;         // Դ�ļ�
//	CString strDestFile;        // Ŀ���ļ�
//	for (int nodeCount = 0; nodeCount < nodeList->Getlength(); nodeCount++)
//	{
//		MSXML2::IXMLDOMNodePtr nodePtr = nodeList->nextNode();
//		_variant_t strCaseNodeName = nodePtr->GetnodeName();
//		_variant_t strCaseNodeValue = nodePtr->Gettext();
//		BSTR bStrTemp = strCaseNodeName.bstrVal;
//		CString strTemp = CString(bStrTemp);
//		SysFreeString(bStrTemp);
//		CString strNodeName = strTemp;
//		//  �ڵ��ֵ�����ȡ�ã�
//		if (0 == strNodeName.CompareNoCase(_T("NO")))
//		{
//			strNo = (BSTR)strCaseNodeValue.pbstrVal;
//
//			// ȡ�õ�ֵ���Դ�ӡ����
//			printf(strNo);
//		}
//
//		// �ڵ�������ֵ������ô����
//		else if (0 == strNodeName.CompareNoCase(_T("CopyFile")))
//		{
//			strSrcFile.Empty();
//			strDestFile.Empty();
//			// ȡ�ýڵ������ֵ
//			MSXML2::IXMLDOMNamedNodeMapPtr pDOMAttrList= nodePtr->Getattributes();
//			for (int j = 0; j < pDOMAttrList->Getlength(); j++)
//			{
//				MSXML2::IXMLDOMNodePtr pDOMAttr= pDOMAttrList->Getitem(j); 
//				// ȡ��Դ�ļ�·��
//				if (CompareNoCase((char*)pDOMAttr->GetnodeName(), _T("src")))
//				{
//					strSrcFile = pDOMAttr->GetnodeTypedValue();
//					// ȡ��Ŀ���ļ�·��
//				} else if (CompareNoCase((char*)pDOMAttr->GetnodeName(), _T("dest")))
//				{
//					strDestFile =pDOMAttr->GetnodeTypedValue();
//				}
//
//				printf("strSrcFile = %s\n", strSrcFile);
//				printf("strDestFile = %s\n", strDestFile );
//			}
//		}
//		else if (0 == strNodeName.CompareNoCase(_T("DelFile")))
//		{
//			strDestFile.Empty();
//			strDestFile = CString((BSTR)strCaseNodeValue.pbstrVal);
//
//			printf("strDestFile = %s\n", strDestFile );
//		}
//	}
//}



void CDlgXml::OnBnClickedBtnConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("���"));
	WriteXml();
}
