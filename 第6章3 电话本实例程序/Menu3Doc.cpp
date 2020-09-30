
// Menu3Doc.cpp : CMenu3Doc 类的实现
//

#include "stdafx.h"
#include "Menu3.h"

#include "Menu3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu3Doc

IMPLEMENT_DYNCREATE(CMenu3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMenu3Doc, CDocument)
END_MESSAGE_MAP()


// CMenu3Doc 构造/析构

CMenu3Doc::CMenu3Doc()
{
	// TODO: 在此添加一次性构造代码

}

CMenu3Doc::~CMenu3Doc()
{
}

BOOL CMenu3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMenu3Doc 序列化

void CMenu3Doc::Serialize(CArchive& ar)
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


// CMenu3Doc 诊断

#ifdef _DEBUG
void CMenu3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenu3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMenu3Doc 命令
