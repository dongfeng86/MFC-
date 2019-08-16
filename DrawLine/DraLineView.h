
// DraLineView.h : CDraLineView 类的接口
//


#pragma once


class CDraLineView : public CView
{
protected: // 仅从序列化创建
	CDraLineView();
	DECLARE_DYNCREATE(CDraLineView)

// 属性
public:
	CDraLineDoc* GetDocument() const;

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
	virtual ~CDraLineView();
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

	//增加了窗口过程函数
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

#ifndef _DEBUG  // DraLineView.cpp 中的调试版本
inline CDraLineDoc* CDraLineView::GetDocument() const
   { return reinterpret_cast<CDraLineDoc*>(m_pDocument); }
#endif

