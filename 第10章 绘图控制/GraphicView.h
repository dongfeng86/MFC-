
// GraphicView.h : CGraphicView 类的接口
//


#pragma once


class CGraphicView : public CView
{
protected: // 仅从序列化创建
	CGraphicView();
	DECLARE_DYNCREATE(CGraphicView)

// 属性
public:
	CGraphicDoc* GetDocument() const;

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
	virtual ~CGraphicView();
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

#ifndef _DEBUG  // GraphicView.cpp 中的调试版本
inline CGraphicDoc* CGraphicView::GetDocument() const
   { return reinterpret_cast<CGraphicDoc*>(m_pDocument); }
#endif

