#include "StdAfx.h"
#include "Graph.h"

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
