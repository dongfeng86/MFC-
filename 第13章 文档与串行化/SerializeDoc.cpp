
// SerializeDoc.cpp : CSerializeDoc ���ʵ��
//

#include "stdafx.h"
#include "Serialize.h"

#include "SerializeDoc.h"
#include "SerializeView.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerializeDoc

IMPLEMENT_DYNCREATE(CSerializeDoc, CDocument)

BEGIN_MESSAGE_MAP(CSerializeDoc, CDocument)
END_MESSAGE_MAP()


// CSerializeDoc ����/����

CSerializeDoc::CSerializeDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSerializeDoc::~CSerializeDoc()
{
}

BOOL CSerializeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	//SetTitle(_T("http://www.sunxin.org"));

	return TRUE;
}


void CSerializeDoc::Serialize(CArchive& ar)
{
	POSITION pos=GetFirstViewPosition();
	CSerializeView* pView=(CSerializeView*)GetNextView(pos);

	//if (ar.IsStoring())
	//{
	//	int iCount=pView->m_obArray.GetSize();
	//	ar<<iCount;
	//	for(int i=0;i<iCount;i++)
	//	{
	//		ar<<pView->m_obArray.GetAt(i);
	//	}
	//}
	//else
	//{
	//	int iCount;
	//	ar>>iCount;
	//	CGraph* pGraph;
	//	for(int i=0;i<iCount;i++)
	//	{
	//		ar>>pGraph;
	//		pView->m_obArray.Add(pGraph);
	//	}
	//}
	//pView->m_obArray.Serialize(ar);
	m_obArray.Serialize(ar);
}

// CSerializeDoc ���
#ifdef _DEBUG
void CSerializeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSerializeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSerializeDoc ����

void CSerializeDoc::DeleteContents()
{
	// TODO: �ڴ����ר�ô����/����û���
	int iCount;
	iCount=m_obArray.GetSize();
	for(int i=0;i<iCount;i++)
	{
		delete m_obArray.GetAt(i);
	}
	m_obArray.RemoveAll();		

	CDocument::DeleteContents();
}
