
// WriteXMLDlg.h : 头文件
//

#pragma once


// CWriteXMLDlg 对话框
class CWriteXMLDlg : public CDialog
{
// 构造
public:
	CWriteXMLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WRITEXML };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnWritexml();
	afx_msg void OnBnClickedBtnWriteinit();
	afx_msg void OnBnClickedBtnReadini();
	afx_msg void OnBnClickedBtnReadxml();
};
