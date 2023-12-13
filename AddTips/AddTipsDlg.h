
// AddTipsDlg.h: 头文件
//

#pragma once


// CAddTipsDlg 对话框
class CAddTipsDlg : public CDialogEx
{
// 构造
public:
	CAddTipsDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_DLG_ADDTIPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CToolTipCtrl m_wndTipContrl;
public:
	afx_msg void OnBnSetfocusChk1st();
private:
	CButton m_wndChk1st;
};
