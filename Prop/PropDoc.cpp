
// PropDoc.cpp : CPropDoc ���ʵ��
//

#include "stdafx.h"
#include "Prop.h"

#include "PropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropDoc

IMPLEMENT_DYNCREATE(CPropDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropDoc, CDocument)
END_MESSAGE_MAP()


// CPropDoc ����/����

CPropDoc::CPropDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPropDoc::~CPropDoc()
{
}

BOOL CPropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPropDoc ���л�

void CPropDoc::Serialize(CArchive& ar)
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


// CPropDoc ���

#ifdef _DEBUG
void CPropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPropDoc ����
