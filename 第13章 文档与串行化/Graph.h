#pragma once

class CGraph:public CObject
{
public:
	DECLARE_SERIAL( CGraph )
	CGraph(void);
	CGraph(UINT nDrawType,CPoint ptOrigin,CPoint ptEnd);
	~CGraph(void);
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;

	void Serialize(CArchive& ar);
	void Draw(CDC *pDc);
};
