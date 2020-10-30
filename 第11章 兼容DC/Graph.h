#pragma once

class CGraph
{
public:
	CGraph(void);
	CGraph(UINT nDrawType,CPoint ptOrigin,CPoint ptEnd);
	~CGraph(void);
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
};
