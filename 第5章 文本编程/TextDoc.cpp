
// TextDoc.cpp : CTextDoc 类的实现
//

#include "stdafx.h"
#include "Text.h"

#include "TextDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextDoc

IMPLEMENT_DYNCREATE(CTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextDoc, CDocument)
END_MESSAGE_MAP()


// CTextDoc 构造/析构

CTextDoc::CTextDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTextDoc::~CTextDoc()
{
}

BOOL CTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTextDoc 序列化

void CTextDoc::Serialize(CArchive& ar)
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


// CTextDoc 诊断

#ifdef _DEBUG
void CTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTextDoc 命令
