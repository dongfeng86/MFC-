
// TestCustomHeaderDlg.h: 头文件
//

#pragma once
#include "CCustomHeader.h"


// CTestDlg 对话框
class CTestDlg : public CDialog
{
// 构造
public:
	CTestDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_TESTCUSTOMHEADER_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_wndLstMain;
	CCustomHeader m_wndHeader;
};
