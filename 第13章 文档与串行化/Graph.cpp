#include "StdAfx.h"
#include "Graph.h"

IMPLEMENT_SERIAL( CGraph, CObject, 1 )

CGraph::CGraph(void)
{
}

CGraph::CGraph(UINT nDrawType,CPoint ptOrigin,CPoint ptEnd)
{
	m_ptOrigin=ptOrigin;
	m_ptEnd=ptEnd;
	m_nDrawType=nDrawType;
}

CGraph::~CGraph(void)
{
}

void CGraph::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar<<m_nDrawType<<m_ptOrigin<<m_ptEnd;
	}
	else
	{
		ar>>m_nDrawType>>m_ptOrigin>>m_ptEnd;
	}
}

void CGraph::Draw(CDC *pDc)
{
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* pOldBrush=pDc->SelectObject(pBrush);
	switch(m_nDrawType)
	{
	case 1:
		pDc->SetPixel(m_ptEnd,RGB(0,0,0));
		break;
	case 2:
		pDc->MoveTo(m_ptOrigin);
		pDc->LineTo(m_ptEnd);
		break;
	case 3:
		pDc->Rectangle(CRect(m_ptOrigin,m_ptEnd));
		break;
	case 4:
		pDc->Ellipse(CRect(m_ptOrigin,m_ptEnd));
		break;
	}

	pDc->SelectObject(pOldBrush);
}
