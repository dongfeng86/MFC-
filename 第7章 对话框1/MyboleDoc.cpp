
// MyboleDoc.cpp : CMyboleDoc ���ʵ��
//

#include "stdafx.h"
#include "Mybole.h"

#include "MyboleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyboleDoc

IMPLEMENT_DYNCREATE(CMyboleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyboleDoc, CDocument)
END_MESSAGE_MAP()


// CMyboleDoc ����/����

CMyboleDoc::CMyboleDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyboleDoc::~CMyboleDoc()
{
}

BOOL CMyboleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMyboleDoc ���л�

void CMyboleDoc::Serialize(CArchive& ar)
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


// CMyboleDoc ���

#ifdef _DEBUG
void CMyboleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyboleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyboleDoc ����
