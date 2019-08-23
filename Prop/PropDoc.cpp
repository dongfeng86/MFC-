
// PropDoc.cpp : CPropDoc 类的实现
//

#include "stdafx.h"
#include "Prop.h"

#include "PropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropDoc

IMPLEMENT_DYNCREATE(CPropDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropDoc, CDocument)
END_MESSAGE_MAP()


// CPropDoc 构造/析构

CPropDoc::CPropDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPropDoc::~CPropDoc()
{
}

BOOL CPropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPropDoc 序列化

void CPropDoc::Serialize(CArchive& ar)
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


// CPropDoc 诊断

#ifdef _DEBUG
void CPropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPropDoc 命令
