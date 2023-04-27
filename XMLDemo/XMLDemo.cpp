// XMLDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <windows.h>
#include <objbase.h>
#include <msxml6.h>

#include <iostream>

// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0)\

// Helper function to create a VT_BSTR variant from a null terminated string. 
HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant)
{
	HRESULT hr = S_OK;
	BSTR bstr = SysAllocString(wszValue);
	CHK_ALLOC(bstr);

	V_VT(&Variant) = VT_BSTR;
	V_BSTR(&Variant) = bstr;

CleanUp:
	return hr;
}

// Helper function to create a DOM instance. 
HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc)
{
	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
	if (SUCCEEDED(hr))
	{
		// these methods should not fail so don't inspect result
		(*ppDoc)->put_async(VARIANT_FALSE);
		(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
		(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
	}
	return hr;
}

//利用DOM加载XML文档
void loadDOMRaw()
{
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMParseError *pXMLErr = NULL;

	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	// XML file name to load
	CHK_HR(VariantFromString(L"stocks.xml", varFileName));
	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus == VARIANT_TRUE)
	{
		CHK_HR(pXMLDom->get_xml(&bstrXML));
		printf("XML DOM loaded from stocks.xml:\n%S\n", bstrXML);
	}
	else
	{
		// Failed to load xml, get last parsing error
		CHK_HR(pXMLDom->get_parseError(&pXMLErr));
		CHK_HR(pXMLErr->get_reason(&bstrErr));
		printf("Failed to load DOM from stocks.xml. %S\n", bstrErr);
	}

CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrXML);
	SysFreeString(bstrErr);
	VariantClear(&varFileName);
}

//利用DOM保存XML文档
void saveDOM()
{
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMParseError *pXMLErr = NULL;
	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;

	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	bstrXML = SysAllocString(L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>");
	CHK_ALLOC(bstrXML);
	CHK_HR(pXMLDom->loadXML(bstrXML, &varStatus));

	if (varStatus == VARIANT_TRUE)
	{
		CHK_HR(pXMLDom->get_xml(&bstrXML));
		printf("XML DOM loaded from app:\n%S\n", bstrXML);

		VariantFromString(L"myData.xml", varFileName);
		CHK_HR(pXMLDom->save(varFileName));
		printf("XML DOM saved to myData.xml\n");
	}
	else
	{
		// Failed to load xml, get last parsing error
		CHK_HR(pXMLDom->get_parseError(&pXMLErr));
		CHK_HR(pXMLErr->get_reason(&bstrErr));
		printf("Failed to load DOM from xml string. %S\n", bstrErr);
	}

CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrXML);
	SysFreeString(bstrErr);
	VariantClear(&varFileName);
}

// Helper function to display parse error.
// It returns error code of the parse error.
HRESULT ReportParseError(IXMLDOMDocument *pDoc, char *szDesc)
{
	HRESULT hr = S_OK;
	HRESULT hrRet = E_FAIL; // Default error code if failed to get from parse error.
	IXMLDOMParseError *pXMLErr = NULL;
	BSTR bstrReason = NULL;

	CHK_HR(pDoc->get_parseError(&pXMLErr));
	CHK_HR(pXMLErr->get_errorCode(&hrRet));
	CHK_HR(pXMLErr->get_reason(&bstrReason));
	printf("%s\n%S\n", szDesc, bstrReason);

CleanUp:
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrReason);
	return hrRet;
}

//查询XML文档节点
void queryNodes()
{
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMNodeList *pNodes = NULL;
	IXMLDOMNode *pNode = NULL;

	BSTR bstrQuery1 = NULL;
	BSTR bstrQuery2 = NULL;
	BSTR bstrNodeName = NULL;
	BSTR bstrNodeValue = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	CHK_HR(VariantFromString(L"stocks.xml", varFileName));
	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus != VARIANT_TRUE)
	{
		CHK_HR(ReportParseError(pXMLDom,(char*) "Failed to load DOM from stocks.xml."));
	}

	// Query a single node.
	//The selectSingleNode method is similar to the selectNodes method, but returns only the first matching node rather than the list of all matching nodes.
	bstrQuery1 = SysAllocString(L"//stock[1]/*");
	CHK_ALLOC(bstrQuery1);
	CHK_HR(pXMLDom->selectSingleNode(bstrQuery1, &pNode));
	if (pNode)
	{
		printf("Result from selectSingleNode:\n");
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		printf("Node, <%S>:\n", bstrNodeName);
		SysFreeString(bstrNodeName);

		CHK_HR(pNode->get_xml(&bstrNodeValue));
		printf("\t%S\n\n", bstrNodeValue);
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);
	}
	else
	{
		CHK_HR(ReportParseError(pXMLDom, (char*)"Error while calling selectSingleNode."));
	}

	// Query a node-set.
	bstrQuery2 = SysAllocString(L"//stock[1]/*");
	CHK_ALLOC(bstrQuery2);
	CHK_HR(pXMLDom->selectNodes(bstrQuery2, &pNodes));
	if (pNodes)
	{
		printf("Results from selectNodes:\n");
		//get the length of node-set
		long length;
		CHK_HR(pNodes->get_length(&length));
		for (long i = 0; i < length; i++)
		{
			CHK_HR(pNodes->get_item(i, &pNode));
			CHK_HR(pNode->get_nodeName(&bstrNodeName));
			printf("Node (%d), <%S>:\n", i, bstrNodeName);
			SysFreeString(bstrNodeName);

			CHK_HR(pNode->get_xml(&bstrNodeValue));
			printf("\t%S\n", bstrNodeValue);
			SysFreeString(bstrNodeValue);
			SAFE_RELEASE(pNode);
		}
	}
	else
	{
		CHK_HR(ReportParseError(pXMLDom,(char *) "Error while calling selectNodes."));
	}

CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pNodes);
	SAFE_RELEASE(pNode);
	SysFreeString(bstrQuery1);
	SysFreeString(bstrQuery2);
	SysFreeString(bstrNodeName);
	SysFreeString(bstrNodeValue);
	VariantClear(&varFileName);
}

int main()
{
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		loadDOMRaw();
		saveDOM();
		queryNodes();
		CoUninitialize();
	}

	return 0;
}