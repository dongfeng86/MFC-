
// GraphicDoc.cpp : CGraphicDoc ���ʵ��
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


// CGraphicDoc ����/����

CGraphicDoc::CGraphicDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGraphicDoc::~CGraphicDoc()
{
}

BOOL CGraphicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGraphicDoc ���л�

void CGraphicDoc::Serialize(CArchive& ar)
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


// CGraphicDoc ���

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


// CGraphicDoc ����
