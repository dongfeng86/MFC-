
// GraphicSaveView.h : CGraphicSaveView 类的接口
//


#pragma once


class CGraphicSaveView : public CScrollView
{
protected: // 仅从序列化创建
	CGraphicSaveView();
	DECLARE_DYNCREATE(CGraphicSaveView)

// 属性
public:
	CGraphicSaveDoc* GetDocument() const;

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
	virtual ~CGraphicSaveView();
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

#ifndef _DEBUG  // GraphicSaveView.cpp 中的调试版本
inline CGraphicSaveDoc* CGraphicSaveView::GetDocument() const
   { return reinterpret_cast<CGraphicSaveDoc*>(m_pDocument); }
#endif

