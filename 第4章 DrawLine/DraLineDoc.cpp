
// DraLineDoc.cpp : CDraLineDoc ���ʵ��
//

#include "stdafx.h"
#include "DraLine.h"

#include "DraLineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraLineDoc

IMPLEMENT_DYNCREATE(CDraLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CDraLineDoc, CDocument)
END_MESSAGE_MAP()


// CDraLineDoc ����/����

CDraLineDoc::CDraLineDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDraLineDoc::~CDraLineDoc()
{
}

BOOL CDraLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDraLineDoc ���л�

void CDraLineDoc::Serialize(CArchive& ar)
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


// CDraLineDoc ���

#ifdef _DEBUG
void CDraLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDraLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDraLineDoc ����
