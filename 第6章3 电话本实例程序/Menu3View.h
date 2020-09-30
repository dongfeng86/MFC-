
// Menu3View.h : CMenu3View 类的接口
//


#pragma once

class CMenu3Doc;
class CMenu3View : public CView
{
protected: // 仅从序列化创建
	CMenu3View();
	DECLARE_DYNCREATE(CMenu3View)

// 属性
public:
	CMenu3Doc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMenu3View();
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

#ifndef _DEBUG  // Menu3View.cpp 中的调试版本
inline CMenu3Doc* CMenu3View::GetDocument() const
   { return reinterpret_cast<CMenu3Doc*>(m_pDocument); }
#endif

