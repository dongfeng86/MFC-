
// SerializeView.h : CSerializeView ��Ľӿ�
//


#pragma once


class CSerializeView : public CView
{
protected: // �������л�����
	CSerializeView();
	DECLARE_DYNCREATE(CSerializeView)

// ����
public:
	CSerializeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSerializeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnWrite();
	//afx_msg void OnRead();
	afx_msg void OnDot();
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnEllispe();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	int m_nDrawType;
	CPoint m_ptOrigin;

	//CObArray m_obArray;
};

#ifndef _DEBUG  // SerializeView.cpp �еĵ��԰汾
inline CSerializeDoc* CSerializeView::GetDocument() const
   { return reinterpret_cast<CSerializeDoc*>(m_pDocument); }
#endif

