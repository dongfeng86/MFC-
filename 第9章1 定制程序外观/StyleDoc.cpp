
// StyleDoc.cpp : CStyleDoc ���ʵ��
//

#include "stdafx.h"
#include "Style.h"

#include "StyleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStyleDoc

IMPLEMENT_DYNCREATE(CStyleDoc, CDocument)

BEGIN_MESSAGE_MAP(CStyleDoc, CDocument)
END_MESSAGE_MAP()


// CStyleDoc ����/����

CStyleDoc::CStyleDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CStyleDoc::~CStyleDoc()
{
}

BOOL CStyleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CStyleDoc ���л�

void CStyleDoc::Serialize(CArchive& ar)
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


// CStyleDoc ���

#ifdef _DEBUG
void CStyleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStyleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStyleDoc ����
