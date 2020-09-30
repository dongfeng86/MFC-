
// Menu2Doc.cpp : CMenu2Doc 类的实现
//

#include "stdafx.h"
#include "Menu2.h"

#include "Menu2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu2Doc

IMPLEMENT_DYNCREATE(CMenu2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMenu2Doc, CDocument)
END_MESSAGE_MAP()


// CMenu2Doc 构造/析构

CMenu2Doc::CMenu2Doc()
{
	// TODO: 在此添加一次性构造代码

}

CMenu2Doc::~CMenu2Doc()
{
}

BOOL CMenu2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMenu2Doc 序列化

void CMenu2Doc::Serialize(CArchive& ar)
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


// CMenu2Doc 诊断

#ifdef _DEBUG
void CMenu2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenu2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMenu2Doc 命令
