
// PropView.h : CPropView ��Ľӿ�
//


#pragma once


class CPropView : public CView
{
protected: // �������л�����
	CPropView();
	DECLARE_DYNCREATE(CPropView)

// ����
public:
	CPropDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CPropView();
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
	afx_msg void OnPropsheet();

private:
	int m_iOccupation;
	BOOL m_bLike[4];
	CString m_strSalary;
	CString m_strWorkerAddr;
};

#ifndef _DEBUG  // PropView.cpp �еĵ��԰汾
inline CPropDoc* CPropView::GetDocument() const
   { return reinterpret_cast<CPropDoc*>(m_pDocument); }
#endif

