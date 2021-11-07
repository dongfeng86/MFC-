
// AdaptiveEditDlg.h: 头文件
//

#pragma once


// CAdaptiveEditDlg 对话框
class CAdaptiveEditDlg : public CDialogEx
{
// 构造
public:
	CAdaptiveEditDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_DLG_ADAPTIVEEDIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_wndEdtSizeable;
	afx_msg void OnEnChangeEdtSizeable();
};
