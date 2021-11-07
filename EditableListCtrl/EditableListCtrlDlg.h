﻿
// EditableListCtrlDlg.h: 头文件
//

#pragma once


// CEditableListCtrlDlg 对话框
class CEditableListCtrlDlg : public CDialog
{
public:
	CEditableListCtrlDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_DLG_EDITABLELISTCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_wndLstEdit;
};
