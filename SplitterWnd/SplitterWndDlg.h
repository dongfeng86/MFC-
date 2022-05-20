
// SplitterWndDlg.h: 头文件
//

#pragma once

//这个地方替换为自己的版本
//#include "CxSplitterWnd.h"
#include "CVertSplitter.h"



// CSplitterWndDlg 对话框
class CSplitterWndDlg : public CDialog
{
public:
	CSplitterWndDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_SPLITTERWND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	//CxSplitterWnd m_wndXSplitter;
	CVertSplitter m_wndXSplitter;
};
