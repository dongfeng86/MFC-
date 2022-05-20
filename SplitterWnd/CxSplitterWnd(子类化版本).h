#pragma once

#define WM_SPLITTER_HOR_MOVED (WM_USER+1000)

class CxSplitterWnd : public CWnd
{
public:
	CxSplitterWnd();
	virtual ~CxSplitterWnd();

	//绑定该类与控件，pParent指控件的父窗口，idCtrl指控件ID
	BOOL BindWithCtrl(CWnd* pParent, DWORD idCtrl);	
	//解除控件与该类的绑定关系
	void UnbindCtrl();
	//设置移动分割条过程中对话框两侧的最小距离
	void SetMinWidth(int left, int right);	
	//分割条左侧的控件ID
	BOOL AttachCtrlAsLeftPane(DWORD idCtrl);
	//分割条右侧的控件ID
	BOOL AttachCtrlAsRightPane(DWORD idCtrl);
	//拆离分割条左右两侧的控件
	BOOL DetachAllPanes();
	//根据分割条位置，调整对话框上所有控件位置
	void AdjustLayout();

protected:
	//分割条可以移动的范围
	BOOL GetMouseClipRect(LPRECT rcClip, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CWnd* m_pParent;
	int m_iLeftMin, m_iRightMin;
	CDWordArray m_idLeft, m_idRight;
};