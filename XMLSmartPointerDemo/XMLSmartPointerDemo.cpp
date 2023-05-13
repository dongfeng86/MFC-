// XMLSmartPointerDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <tchar.h>
#import <msxml6.dll> //这一句引入了所需要的头文件

//该函数实现实现了以下两个功能
//创建了一个XML DOM对象（pXMLDom），并设置为同步模式（Creates an XML DOM object (pXMLDom) and sets it to synchronous mode.）
//调用pXMLDom的load方法，指定XML文档的路径（Calls the load method on pXMLDom, specifying the path to stocks.xml.）
void loadDOMsmart()
{
	MSXML2::IXMLDOMDocumentPtr pXMLDom;
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
	{
		printf("Failed to instantiate an XML DOM.\n");
		return;
	}

	try
	{
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;

		if (pXMLDom->load("stocks.xml") == VARIANT_TRUE)
		{
			printf("XML DOM loaded from stocks.xml:\n%s\n", (LPCSTR)pXMLDom->xml);
		}
		else
		{
			// Failed to load xml
			printf("Failed to load DOM from stocks.xml. %s\n",
				(LPCSTR)pXMLDom->parseError->Getreason());
		}
	}
	catch (_com_error errorObject)
	{
		printf("Exception thrown, HRESULT: 0x%08x", errorObject.Error());
	}
}


// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

//如何保存一个xml文档
void saveDOMsmart()
{
	MSXML2::IXMLDOMDocumentPtr pXMLDom = NULL;
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);

	if (FAILED(hr))
	{
		printf("Failed to instantiate an XML DOM.\n");
		return;
	}

	try
	{
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;

		if (pXMLDom->loadXML(L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>") == VARIANT_TRUE)
		{
			printf("XML DOM loaded from app:\n%s\n", (LPCSTR)pXMLDom->xml);

			CHK_HR(pXMLDom->save(L"myData.xml"));
			printf("XML DOM saved to myData.xml.\n");
		}
		else
		{
			printf("Failed to load DOM from xml string. %s\n", (LPCSTR)pXMLDom->parseError->Getreason());
		}
	}
	catch (_com_error errorObject)
	{
		printf("Exception thrown, HRESULT: 0x%08x", errorObject.Error());
	}

CleanUp:
	return;
}

//查询一个节点
void queryNodesSmart()
{
	MSXML2::IXMLDOMDocumentPtr pXMLDom;
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
	{
		printf("Failed to instantiate an XML DOM.\n");
		return;
	}

	try
	{
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;

		if (pXMLDom->load(L"stocks.xml") != VARIANT_TRUE)
		{
			CHK_HR(pXMLDom->parseError->errorCode);
			printf("Failed to load DOM from stocks.xml.\n%s\n",
				(LPCSTR)pXMLDom->parseError->Getreason());
		}

		//This expression specifies all the child elements of the first <stock> element in the XML document.
		//In MSXML, the selectSingleNode method returns the first element of the resultant node-set, 
		//and the selectNodes method returns all the elements in the node-set.
		MSXML2::IXMLDOMNodePtr pNode = pXMLDom->selectSingleNode(L"//stock[1]/*");
		if (pNode)
		{
			printf("Result from selectSingleNode:\nNode, <%s>:\n\t%s\n\n",
				(LPCSTR)pNode->nodeName, (LPCSTR)pNode->xml);
		}
		else
		{
			printf("No node is fetched.\n");
		}

		// Query a node-set.
		MSXML2::IXMLDOMNodeListPtr pnl = pXMLDom->selectNodes(L"//stock[1]/*");
		if (pnl)
		{
			printf("Results from selectNodes:\n");
			for (long i = 0; i < pnl->length; i++)
			{
				pNode = pnl->item[i];
				printf("Node (%d), <%s>:\n\t%s\n",
					i, (LPCSTR)pNode->nodeName, (LPCSTR)pnl->item[i]->xml);
			}
		}
		else
		{
			printf("No node set is fetched.\n");
		}
	}
	catch (_com_error errorObject)
	{
		printf("Exception thrown, HRESULT: 0x%08x", errorObject.Error());
	}

CleanUp:
	return;
}

//增加一个节点
void addNodeSmart()
{
	MSXML2::IXMLDOMDocumentPtr pXMLDom;
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
	{
		printf("Failed to instantiate an XML DOM.\n");
		return;
	}

	try
	{
		pXMLDom->async = VARIANT_FALSE;
		pXMLDom->validateOnParse = VARIANT_FALSE;
		pXMLDom->resolveExternals = VARIANT_FALSE;

		if (pXMLDom->load(L"stocks.xml") != VARIANT_TRUE)
		{
			CHK_HR(pXMLDom->parseError->errorCode);
			printf("Failed to load DOM from stocks.xml.\n%s\n",
				(LPCSTR)pXMLDom->parseError->Getreason());
		}

		//获取根元素
		MSXML2::IXMLDOMElementPtr pNode = pXMLDom->GetdocumentElement();

		//下面一句获取根元素下第一个stock元素，不删除备用
		//MSXML2::IXMLDOMNodePtr pNode = pXMLDom->selectSingleNode(L"//stock[1]/*");	
		if (pNode)
		{
			MSXML2::IXMLDOMElementPtr pNewElement = NULL;
			pNewElement = pXMLDom->createElement(L"NewNode");
			pNewElement->put_text(L"通过程序添加的第一个子节点");
			pNode->appendChild(pNewElement);
			pXMLDom->save(L"stocksNew.xml");	//保存才会生效
			printf("XML DOM loaded from stocksNew.xml:\n%s\n", (LPCSTR)pXMLDom->xml);
		}
		else
		{
			printf("No node is fetched.\n");
		}
	}
	catch (_com_error errorObject)
	{
		printf("Exception thrown, HRESULT: 0x%08x", errorObject.Error());
	}

CleanUp:
	return;
}


void TestWriteXml()
{
	MSXML2::IXMLDOMDocumentPtr spXmldoc;
	HRESULT hr = spXmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);

	if (SUCCEEDED(hr))
	{
		VARIANT_BOOL isSuccessFul;
		//CComVariant varXmlFile(L"tlacd.xml");

		//spXmldoc->put_async(VARIANT_FALSE);  
		if (spXmldoc->load(L"tlacd.xml") != VARIANT_TRUE)
		{
			if (FAILED(spXmldoc->parseError->errorCode))
				return;
			printf("Failed to load DOM from stocks.xml.\n%s\n",
				(LPCSTR)spXmldoc->parseError->Getreason());
		}

			
			//CComBSTR bstrXml;
			//CComPtr<IXMLDOMElement> spRoot = NULL;
			MSXML2::IXMLDOMElementPtr spRoot;
			//CComPtr<IXMLDOMElement> spTheBook = NULL;
			MSXML2::IXMLDOMElementPtr spTheBook;
			//CComPtr<IXMLDOMElement> spTheElem = NULL;
			MSXML2::IXMLDOMElementPtr spTheElem = NULL;
			//CComPtr<IXMLDOMNode> spNewNode = NULL;
			MSXML2::IXMLDOMNodePtr spNewNode;

			spRoot = spXmldoc->GetdocumentElement();
			//hr = spXmldoc->get_documentElement(&spRoot);
			//spRoot->get_xml(&bstrXml);
			//AfxMessageBox(L"1, 原始的XML");
			//AfxMessageBox((LPCTSTR)spRoot->xml);

			//spXmldoc->createElement(L"book", &spTheBook);
			spTheBook = spXmldoc->createElement(L"book");
			//spXmldoc->createElement(L"name", &spTheElem);
			spTheElem = spXmldoc->createElement(L"name");
			//spTheBook->appendChild(spTheElem, &spNewNode);
			spTheElem->put_text(L"新书");
			spNewNode = spTheBook->appendChild(spTheElem);
			spTheElem.Release();
			spNewNode.Release();

			//spXmldoc->createElement(L"price", &spTheElem);
			spTheElem = spXmldoc->createElement(L"price");
			spTheElem->put_text(L"20");
			//spTheBook->appendChild(spTheElem, &spNewNode);
			spNewNode =spTheBook->appendChild(spTheElem);
			spTheElem.Release();
			spNewNode.Release();

			//spXmldoc->createElement(L"memo", &spTheElem);
			spTheElem = spXmldoc->createElement(L"memo");
			spTheElem->put_text(L"新书的更好看。");
			spNewNode = spTheBook->appendChild(spTheElem);
			spNewNode.Release();
			spTheElem.Release();

			spNewNode = spRoot->appendChild(spTheBook);
			spNewNode.Release();
			spTheBook.Release();

			spXmldoc->save(L"tlacd.xml");
			//spXmldoc->save(varXmlFile); //保存xml。  


			//AfxMessageBox(L"2, 新建一本书完成");
			//AfxMessageBox(spRoot->xml);
			////---  新建一本书完成 ----  


			/*

////---  下面对《哈里波特》做一些修改。 ----  
////---  查询找《哈里波特》----  
			CComPtr<IXMLDOMNode> spTheNode = NULL;
			spRoot->selectSingleNode(L"/books/book[name='哈里波特']", &spTheNode);
			hr = spTheNode.QueryInterface(&spTheBook);
			spTheNode.Release();

			spTheBook->get_xml(&bstrXml);
			AfxMessageBox(L"3,《哈里波特》的XML");
			AfxMessageBox(bstrXml);

			////---  此时修改这本书的价格 -----  
			CComPtr<IXMLDOMNodeList> spNodeList = NULL;
			CComPtr<IXMLDOMNode> spListItem = NULL;
			spTheBook->get_childNodes(&spNodeList);
			spNodeList->get_item(1, &spListItem);
			spNodeList.Release();
			spListItem->put_text(L"15");

			////---  另外还想加一个属性id，值为B01 ----  
			CComVariant varId(L"B01");
			spTheBook->setAttribute(L"id", varId);
			varId.Clear();

			spTheBook->get_xml(&bstrXml);
			spTheBook.Release();
			AfxMessageBox(L"4, 对《哈里波特》修改完成。");
			AfxMessageBox(bstrXml);
			////---  对《哈里波特》修改完成。 ----  


////---  要用id属性删除《三国演义》这本书  ----  
			spRoot->selectSingleNode(L"/books/book[@id='B02']", &spTheNode);
			hr = spTheNode.QueryInterface(&spTheBook);
			spTheNode.Release();

			spTheBook->get_xml(&bstrXml);
			AfxMessageBox(L"5, 《三国演义》的XML");
			AfxMessageBox(bstrXml);

			CComPtr<IXMLDOMNode> spParentNode = NULL;
			spTheBook->get_parentNode(&spParentNode);
			spParentNode->removeChild(spTheBook, &spTheNode);
			spTheNode.Release();
			spParentNode.Release();
			spTheBook.Release();

			spRoot->get_xml(&bstrXml);
			AfxMessageBox(L"6, 删除《三国演义》后的XML");
			AfxMessageBox(bstrXml);


			////---  再将所有价格低于10的书删除  ----  
			spRoot->selectNodes(L"/books/book[price<10]", &spNodeList);
			CComQIPtr<IXMLDOMSelection> spSomeBooks = spNodeList;
			spNodeList.Release();

			spSomeBooks->removeAll();
			spSomeBooks.Release();

			spXmldoc->get_xml(&bstrXml);
			AfxMessageBox(L"7, 已经删除价格低于10的书");
			AfxMessageBox(bstrXml);

			spRoot.Release();
			bstrXml.Empty();

			//spXmldoc->save(varXmlFile); //保存xml。  
			*/


	}

	//spXmldoc.Release();
}


int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		loadDOMsmart();
		saveDOMsmart();
		queryNodesSmart();
		addNodeSmart();
		CoUninitialize();
	}

	return 0;
}