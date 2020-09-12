// DlgXml.cpp : 实现文件
//

#include "stdafx.h"
#import "msxml3.dll" 
using namespace MSXML2;

#include "读写XML文件.h"
#include "DlgXml.h"



// CDlgXml 对话框

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
//		MessageBox(_T("创建DOMDocument对象失败。\n请检查运行环境"), _T("错误"), MB_ICONERROR); 
//		return;
//	}
//	// 读取xml
//	pDoc->put_async(VARIANT_FALSE);
//	VARIANT_BOOL bhr = pDoc->load((_variant_t)strXmlPath);
//
//	if (bhr != VARIANT_TRUE) {
//		MessageBox(_T("无法正确读取xml文件"), _T("错误"), MB_ICONERROR);
//		return;
//	}
//
//	// 根节点取得
//	MSXML2::IXMLDOMElementPtr root = pDoc->documentElement;
//	// 取得根节点的名字
//	_variant_t strRootName = root->nodeName;
//	_bstr_t wstrRootName(strRootName.bstrVal);
//	MSXML2::IXMLDOMNodeListPtr nodeList = root->GetchildNodes();//cases
//
//	// 解析cases的子节点
//	ReadCase(nodeList);
//}

//void CDlgXml::ReadXml()
//{
//	::CoInitialize(NULL);
//	MSXML2::IXMLDOMElementPtr xRoot;  
//	MSXML2::IXMLDOMElementPtr xElement;  
//	MSXML2::IXMLDOMNodeListPtr xNodes; //某个节点的所以字节点  
//	MSXML2::IXMLDOMNamedNodeMapPtr xNodeAtts;//某个节点的所有属性;  
//	MSXML2::IXMLDOMNodePtr xNode;  
//	static MSXML2::IXMLDOMDocumentPtr xDoc;
//	HRESULT HR = xDoc.CreateInstance(_uuidof(MSXML2::DOMDocument30));  
//	if(!SUCCEEDED(HR))  
//	{  
//		return;  
//	}  
//	xDoc->load((_variant_t)m_fileProjectPath);
//	xRoot = xDoc->GetdocumentElement();//获得根节点;  
//	xRoot->get_childNodes(&xNodes);//获得根节点的所有子节点;  
//	long xNodesNum,AttsNum;
//	xNodes->get_length(&xNodesNum);//获得所有子节点的个数;  
//
//
//	for(int i = 0; i < xNodesNum; i++)  
//	{  
//		xNodes->get_item(i, &xNode);//获得某个子节点;  
//
//		CString  sBaseName = CString(((string)xNode->GetbaseName()).c_str());
//		xNode->get_attributes(&xNodeAtts);//获得某个节点的所有属性;  
//		xNodeAtts->get_length(&AttsNum);//获得所有属性的个数; 
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
//				xNodeAtts->get_item(j, &xNodeItem);//获得某个属性;  
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
//	// 创建根结点
//	MSXML2::IXMLDOMElementPtr pXMLRoot= NULL; 
//	pXMLRoot = xDoc->createElement("SmokeControlConfig");
//	pXMLRoot->setAttribute("Name", "天正防排烟配置");
//	// 添加根结点
//	xDoc->appendChild(pXMLRoot); 
//
//	// 创建下级元素结点
//	MSXML2::IXMLDOMElementPtr pXMLEle = NULL;
//	pXMLEle = xDoc->createElement("Project");
//	pXMLEle->setAttribute("Name", (_variant_t)sRootText);
//	pXMLEle->setAttribute("Dialog", m_mapDlg[hRootItem].iSceneId);
//	pXMLEle->setAttribute("Scene", (_variant_t)m_mapDlg[hRootItem].sScene);
//	pXMLEle->setAttribute(_T("DlgConfig"), (_variant_t)GetDlgConfig(m_mapDlg[hRootItem].iSceneId, m_mapDlg[hRootItem].pDlg));
//	// 添加元素结点
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
//	CString strNo;              // case编号
//	CString strSrcFile;         // 源文件
//	CString strDestFile;        // 目标文件
//	for (int nodeCount = 0; nodeCount < nodeList->Getlength(); nodeCount++)
//	{
//		MSXML2::IXMLDOMNodePtr nodePtr = nodeList->nextNode();
//		_variant_t strCaseNodeName = nodePtr->GetnodeName();
//		_variant_t strCaseNodeValue = nodePtr->Gettext();
//		BSTR bStrTemp = strCaseNodeName.bstrVal;
//		CString strTemp = CString(bStrTemp);
//		SysFreeString(bStrTemp);
//		CString strNodeName = strTemp;
//		//  节点的值，如何取得？
//		if (0 == strNodeName.CompareNoCase(_T("NO")))
//		{
//			strNo = (BSTR)strCaseNodeValue.pbstrVal;
//
//			// 取得的值可以打印出来
//			printf(strNo);
//		}
//
//		// 节点有属性值，该怎么处理？
//		else if (0 == strNodeName.CompareNoCase(_T("CopyFile")))
//		{
//			strSrcFile.Empty();
//			strDestFile.Empty();
//			// 取得节点的属性值
//			MSXML2::IXMLDOMNamedNodeMapPtr pDOMAttrList= nodePtr->Getattributes();
//			for (int j = 0; j < pDOMAttrList->Getlength(); j++)
//			{
//				MSXML2::IXMLDOMNodePtr pDOMAttr= pDOMAttrList->Getitem(j); 
//				// 取得源文件路径
//				if (CompareNoCase((char*)pDOMAttr->GetnodeName(), _T("src")))
//				{
//					strSrcFile = pDOMAttr->GetnodeTypedValue();
//					// 取得目标文件路径
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
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("你好"));
	WriteXml();
}
