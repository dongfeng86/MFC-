
// DraLineDoc.cpp : CDraLineDoc 类的实现
//

#include "stdafx.h"
#include "DraLine.h"

#include "DraLineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraLineDoc

IMPLEMENT_DYNCREATE(CDraLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CDraLineDoc, CDocument)
END_MESSAGE_MAP()


// CDraLineDoc 构造/析构

CDraLineDoc::CDraLineDoc()
{
	// TODO: 在此添加一次性构造代码

}

CDraLineDoc::~CDraLineDoc()
{
}

BOOL CDraLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDraLineDoc 序列化

void CDraLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CDraLineDoc 诊断

#ifdef _DEBUG
void CDraLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDraLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDraLineDoc 命令
