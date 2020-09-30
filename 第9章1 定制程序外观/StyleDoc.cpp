
// StyleDoc.cpp : CStyleDoc 类的实现
//

#include "stdafx.h"
#include "Style.h"

#include "StyleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStyleDoc

IMPLEMENT_DYNCREATE(CStyleDoc, CDocument)

BEGIN_MESSAGE_MAP(CStyleDoc, CDocument)
END_MESSAGE_MAP()


// CStyleDoc 构造/析构

CStyleDoc::CStyleDoc()
{
	// TODO: 在此添加一次性构造代码

}

CStyleDoc::~CStyleDoc()
{
}

BOOL CStyleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CStyleDoc 序列化

void CStyleDoc::Serialize(CArchive& ar)
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


// CStyleDoc 诊断

#ifdef _DEBUG
void CStyleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStyleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStyleDoc 命令
