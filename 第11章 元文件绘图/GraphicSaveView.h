
// GraphicSaveView.h : CGraphicSaveView ��Ľӿ�
//


#pragma once


class CGraphicSaveView : public CScrollView
{
protected: // �������л�����
	CGraphicSaveView();
	DECLARE_DYNCREATE(CGraphicSaveView)

// ����
public:
	CGraphicSaveDoc* GetDocument() const;

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
	virtual ~CGraphicSaveView();
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
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
	afx_msg void OnDot();
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnEllispe();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPtrArray m_arpObjects;
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
private:
	CMetaFileDC m_dcMetaFile;
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
};

#ifndef _DEBUG  // GraphicSaveView.cpp �еĵ��԰汾
inline CGraphicSaveDoc* CGraphicSaveView::GetDocument() const
   { return reinterpret_cast<CGraphicSaveDoc*>(m_pDocument); }
#endif

