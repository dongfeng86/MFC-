
// FileDoc.cpp : CFileDoc ���ʵ��
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


// CFileDoc ����/����

CFileDoc::CFileDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CFileDoc::~CFileDoc()
{
}

BOOL CFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFileDoc ���л�

void CFileDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CFileDoc ���

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


// CFileDoc ����
