
// WinIniDoc.cpp : CWinIniDoc 类的实现
//

#include "stdafx.h"
#include "WinIni.h"

#include "WinIniDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinIniDoc

IMPLEMENT_DYNCREATE(CWinIniDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinIniDoc, CDocument)
END_MESSAGE_MAP()


// CWinIniDoc 构造/析构

CWinIniDoc::CWinIniDoc()
{
	// TODO: 在此添加一次性构造代码

}

CWinIniDoc::~CWinIniDoc()
{
}

BOOL CWinIniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CWinIniDoc 序列化

void CWinIniDoc::Serialize(CArchive& ar)
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


// CWinIniDoc 诊断

#ifdef _DEBUG
void CWinIniDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinIniDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinIniDoc 命令
