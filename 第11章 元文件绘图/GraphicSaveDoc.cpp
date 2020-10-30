
// GraphicSaveDoc.cpp : CGraphicSaveDoc 类的实现
//

#include "stdafx.h"
#include "GraphicSave.h"

#include "GraphicSaveDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicSaveDoc

IMPLEMENT_DYNCREATE(CGraphicSaveDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicSaveDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicSaveDoc 构造/析构

CGraphicSaveDoc::CGraphicSaveDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGraphicSaveDoc::~CGraphicSaveDoc()
{
}

BOOL CGraphicSaveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGraphicSaveDoc 序列化

void CGraphicSaveDoc::Serialize(CArchive& ar)
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


// CGraphicSaveDoc 诊断

#ifdef _DEBUG
void CGraphicSaveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicSaveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicSaveDoc 命令
