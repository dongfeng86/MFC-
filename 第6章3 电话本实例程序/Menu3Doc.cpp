
// Menu3Doc.cpp : CMenu3Doc ���ʵ��
//

#include "stdafx.h"
#include "Menu3.h"

#include "Menu3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu3Doc

IMPLEMENT_DYNCREATE(CMenu3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMenu3Doc, CDocument)
END_MESSAGE_MAP()


// CMenu3Doc ����/����

CMenu3Doc::CMenu3Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CMenu3Doc::~CMenu3Doc()
{
}

BOOL CMenu3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMenu3Doc ���л�

void CMenu3Doc::Serialize(CArchive& ar)
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


// CMenu3Doc ���

#ifdef _DEBUG
void CMenu3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenu3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMenu3Doc ����
