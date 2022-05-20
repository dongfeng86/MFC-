
// AddToolBarDlg.h: 头文件
//

#pragma once


// CAddToolBarDlg 对话框
class CAddToolBarDlg : public CDialog
{
// 构造
public:
	CAddToolBarDlg(CWnd* pParent = nullptr);	// 标准构造函数

	enum { IDD = IDD_ADDTOOLBAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnFirst(void);
	afx_msg void OnBtnSecond(void);
	DECLARE_MESSAGE_MAP()

private:
	CToolBar m_wndToolBar;
};
