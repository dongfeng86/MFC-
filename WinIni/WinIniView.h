
// WinIniView.h : CWinIniView ��Ľӿ�
//


#pragma once


class CWinIniView : public CView
{
protected: // �������л�����
	CWinIniView();
	DECLARE_DYNCREATE(CWinIniView)

// ����
public:
	CWinIniDoc* GetDocument() const;

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
	virtual ~CWinIniView();
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
	afx_msg void OnWritereg();
	afx_msg void OnReadreg();
};

#ifndef _DEBUG  // WinIniView.cpp �еĵ��԰汾
inline CWinIniDoc* CWinIniView::GetDocument() const
   { return reinterpret_cast<CWinIniDoc*>(m_pDocument); }
#endif
