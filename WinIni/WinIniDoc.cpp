
// WinIniDoc.cpp : CWinIniDoc ���ʵ��
//

#include "stdafx.h"
#include "WinIni.h"

#include "WinIniDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinIniDoc

IMPLEMENT_DYNCREATE(CWinIniDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinIniDoc, CDocument)
END_MESSAGE_MAP()


// CWinIniDoc ����/����

CWinIniDoc::CWinIniDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CWinIniDoc::~CWinIniDoc()
{
}

BOOL CWinIniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CWinIniDoc ���л�

void CWinIniDoc::Serialize(CArchive& ar)
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


// CWinIniDoc ���

#ifdef _DEBUG
void CWinIniDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinIniDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinIniDoc ����
