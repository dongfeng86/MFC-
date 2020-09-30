
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#define  UM_PROGRESS WM_USER+1

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	//CMFCToolBar m_wndToolBarNew;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcons[3];
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTest();
	CMFCToolBar m_wndToolBarNew;
	afx_msg void OnShoworhide();
	afx_msg void OnUpdateShoworhide(CCmdUI *pCmdUI);
	afx_msg LRESULT  OnProgress(WPARAM wParam,LPARAM lParam);

	CProgressCtrl m_wndProgress;

	afx_msg void OnPaint();
};


