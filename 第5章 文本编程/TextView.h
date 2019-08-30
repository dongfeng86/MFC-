
// TextView.h : CTextView 类的接口
//


#pragma once
#include "atltypes.h"


class CTextView : public CView
{
protected: // 仅从序列化创建
	CTextView();
	DECLARE_DYNCREATE(CTextView)

// 属性
public:
	CTextDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
	CBitmap m_bitmap;
	CString m_strLine;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CPoint m_ptOrigin;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_iWidth;
};

#ifndef _DEBUG  // TextView.cpp 中的调试版本
inline CTextDoc* CTextView::GetDocument() const
   { return reinterpret_cast<CTextDoc*>(m_pDocument); }
#endif

