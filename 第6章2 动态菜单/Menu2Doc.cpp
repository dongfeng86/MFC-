
// Menu2Doc.cpp : CMenu2Doc ���ʵ��
//

#include "stdafx.h"
#include "Menu2.h"

#include "Menu2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu2Doc

IMPLEMENT_DYNCREATE(CMenu2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMenu2Doc, CDocument)
END_MESSAGE_MAP()


// CMenu2Doc ����/����

CMenu2Doc::CMenu2Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CMenu2Doc::~CMenu2Doc()
{
}

BOOL CMenu2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMenu2Doc ���л�

void CMenu2Doc::Serialize(CArchive& ar)
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


// CMenu2Doc ���

#ifdef _DEBUG
void CMenu2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenu2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMenu2Doc ����
