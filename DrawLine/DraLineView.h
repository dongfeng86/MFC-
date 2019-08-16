
// DraLineView.h : CDraLineView ��Ľӿ�
//


#pragma once


class CDraLineView : public CView
{
protected: // �������л�����
	CDraLineView();
	DECLARE_DYNCREATE(CDraLineView)

// ����
public:
	CDraLineDoc* GetDocument() const;

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
	virtual ~CDraLineView();
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

	//�����˴��ڹ��̺���
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	CPoint m_ptOrigin;
	CPoint m_ptSec;
	BOOL m_bDraw;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // DraLineView.cpp �еĵ��԰汾
inline CDraLineDoc* CDraLineView::GetDocument() const
   { return reinterpret_cast<CDraLineDoc*>(m_pDocument); }
#endif

