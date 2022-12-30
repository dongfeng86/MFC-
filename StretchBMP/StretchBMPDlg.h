
// StretchBMPDlg.h: 头文件
//

#pragma once


// CStretchBMPDlg 对话框
class CStretchBMPDlg : public CDialog
{
// 构造
public:
	CStretchBMPDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_STRETCHBMP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtn1(void);
	afx_msg void OnBtn2(void);
	DECLARE_MESSAGE_MAP()

private:
	CToolBarCtrl m_wndToolBar;
	CBitmap m_bmpToolBar;
};
