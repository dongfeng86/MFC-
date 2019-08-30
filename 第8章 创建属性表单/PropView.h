
// PropView.h : CPropView 类的接口
//


#pragma once


class CPropView : public CView
{
protected: // 仅从序列化创建
	CPropView();
	DECLARE_DYNCREATE(CPropView)

// 属性
public:
	CPropDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPropView();
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
	afx_msg void OnPropsheet();

private:
	int m_iOccupation;
	BOOL m_bLike[4];
	CString m_strSalary;
	CString m_strWorkerAddr;
};

#ifndef _DEBUG  // PropView.cpp 中的调试版本
inline CPropDoc* CPropView::GetDocument() const
   { return reinterpret_cast<CPropDoc*>(m_pDocument); }
#endif

