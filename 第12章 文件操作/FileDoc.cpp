
// FileDoc.cpp : CFileDoc 类的实现
//

#include "stdafx.h"
#include "File.h"

#include "FileDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileDoc

IMPLEMENT_DYNCREATE(CFileDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileDoc, CDocument)
END_MESSAGE_MAP()


// CFileDoc 构造/析构

CFileDoc::CFileDoc()
{
	// TODO: 在此添加一次性构造代码

}

CFileDoc::~CFileDoc()
{
}

BOOL CFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CFileDoc 序列化

void CFileDoc::Serialize(CArchive& ar)
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


// CFileDoc 诊断

#ifdef _DEBUG
void CFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFileDoc 命令
