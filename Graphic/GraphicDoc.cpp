
// GraphicDoc.cpp : CGraphicDoc 类的实现
//

#include "stdafx.h"
#include "Graphic.h"

#include "GraphicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicDoc

IMPLEMENT_DYNCREATE(CGraphicDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicDoc 构造/析构

CGraphicDoc::CGraphicDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGraphicDoc::~CGraphicDoc()
{
}

BOOL CGraphicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGraphicDoc 序列化

void CGraphicDoc::Serialize(CArchive& ar)
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


// CGraphicDoc 诊断

#ifdef _DEBUG
void CGraphicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicDoc 命令
