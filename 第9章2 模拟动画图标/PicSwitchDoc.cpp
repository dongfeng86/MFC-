
// PicSwitchDoc.cpp : CPicSwitchDoc ���ʵ��
//

#include "stdafx.h"
#include "PicSwitch.h"

#include "PicSwitchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicSwitchDoc

IMPLEMENT_DYNCREATE(CPicSwitchDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicSwitchDoc, CDocument)
END_MESSAGE_MAP()


// CPicSwitchDoc ����/����

CPicSwitchDoc::CPicSwitchDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPicSwitchDoc::~CPicSwitchDoc()
{
}

BOOL CPicSwitchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPicSwitchDoc ���л�

void CPicSwitchDoc::Serialize(CArchive& ar)
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


// CPicSwitchDoc ���

#ifdef _DEBUG
void CPicSwitchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicSwitchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPicSwitchDoc ����
