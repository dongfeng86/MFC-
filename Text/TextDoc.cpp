
// TextDoc.cpp : CTextDoc ���ʵ��
//

#include "stdafx.h"
#include "Text.h"

#include "TextDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextDoc

IMPLEMENT_DYNCREATE(CTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextDoc, CDocument)
END_MESSAGE_MAP()


// CTextDoc ����/����

CTextDoc::CTextDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTextDoc::~CTextDoc()
{
}

BOOL CTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTextDoc ���л�

void CTextDoc::Serialize(CArchive& ar)
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


// CTextDoc ���

#ifdef _DEBUG
void CTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTextDoc ����
