
// MyboleDoc.cpp : CMyboleDoc 类的实现
//

#include "stdafx.h"
#include "Mybole.h"

#include "MyboleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyboleDoc

IMPLEMENT_DYNCREATE(CMyboleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyboleDoc, CDocument)
END_MESSAGE_MAP()


// CMyboleDoc 构造/析构

CMyboleDoc::CMyboleDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMyboleDoc::~CMyboleDoc()
{
}

BOOL CMyboleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMyboleDoc 序列化

void CMyboleDoc::Serialize(CArchive& ar)
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


// CMyboleDoc 诊断

#ifdef _DEBUG
void CMyboleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyboleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyboleDoc 命令
