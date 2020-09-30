
// Menu3View.h : CMenu3View ��Ľӿ�
//


#pragma once

class CMenu3Doc;
class CMenu3View : public CView
{
protected: // �������л�����
	CMenu3View();
	DECLARE_DYNCREATE(CMenu3View)

// ����
public:
	CMenu3Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMenu3View();
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
	afx_msg void OnPhone1();
	afx_msg void OnPhone2();
	afx_msg void OnPhone3();
	afx_msg void OnPhone4();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	int m_iIndex;
	CMenu m_menu;
public:
	CString m_strLine;
	CStringArray m_arsLines;
};

#ifndef _DEBUG  // Menu3View.cpp �еĵ��԰汾
inline CMenu3Doc* CMenu3View::GetDocument() const
   { return reinterpret_cast<CMenu3Doc*>(m_pDocument); }
#endif

