
// GraphicSaveDoc.cpp : CGraphicSaveDoc ���ʵ��
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


// CGraphicSaveDoc ����/����

CGraphicSaveDoc::CGraphicSaveDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGraphicSaveDoc::~CGraphicSaveDoc()
{
}

BOOL CGraphicSaveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGraphicSaveDoc ���л�

void CGraphicSaveDoc::Serialize(CArchive& ar)
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


// CGraphicSaveDoc ���

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


// CGraphicSaveDoc ����
