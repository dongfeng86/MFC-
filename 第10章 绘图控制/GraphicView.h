
// GraphicView.h : CGraphicView ��Ľӿ�
//


#pragma once


class CGraphicView : public CView
{
protected: // �������л�����
	CGraphicView();
	DECLARE_DYNCREATE(CGraphicView)

// ����
public:
	CGraphicDoc* GetDocument() const;

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
	virtual ~CGraphicView();
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
	afx_msg void OnPoint();
	afx_msg void OnLine();
	afx_msg void OnRectange();
	afx_msg void OnEllipse();
private:
	UINT m_nDrawType;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CPoint m_ptOrigin;
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetting();
private:
	UINT m_nLineWidth;
	int m_nLineStyle;
public:
	afx_msg void OnColor();
private:
	COLORREF m_clr;
public:
	afx_msg void OnFont();
private:
	CString m_strFontName;
	CFont m_font;

	//afx_msg void OnPaint();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // GraphicView.cpp �еĵ��԰汾
inline CGraphicDoc* CGraphicView::GetDocument() const
   { return reinterpret_cast<CGraphicDoc*>(m_pDocument); }
#endif

