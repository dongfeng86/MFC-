
// WinIniView.h : CWinIniView 类的接口
//


#pragma once


class CWinIniView : public CView
{
protected: // 仅从序列化创建
	CWinIniView();
	DECLARE_DYNCREATE(CWinIniView)

// 属性
public:
	CWinIniDoc* GetDocument() const;

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
	virtual ~CWinIniView();
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
	afx_msg void OnWritereg();
	afx_msg void OnReadreg();
};

#ifndef _DEBUG  // WinIniView.cpp 中的调试版本
inline CWinIniDoc* CWinIniView::GetDocument() const
   { return reinterpret_cast<CWinIniDoc*>(m_pDocument); }
#endif

