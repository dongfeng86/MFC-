
// PicSwitchDoc.cpp : CPicSwitchDoc 类的实现
//

#include "stdafx.h"
#include "PicSwitch.h"

#include "PicSwitchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicSwitchDoc

IMPLEMENT_DYNCREATE(CPicSwitchDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicSwitchDoc, CDocument)
END_MESSAGE_MAP()


// CPicSwitchDoc 构造/析构

CPicSwitchDoc::CPicSwitchDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPicSwitchDoc::~CPicSwitchDoc()
{
}

BOOL CPicSwitchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPicSwitchDoc 序列化

void CPicSwitchDoc::Serialize(CArchive& ar)
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


// CPicSwitchDoc 诊断

#ifdef _DEBUG
void CPicSwitchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicSwitchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPicSwitchDoc 命令
