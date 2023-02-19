
// DemoComDlg.h: 头文件
//

#pragma once


// CDemoComDlg 对话框
class CDemoComDlg : public CDialog
{
// 构造
public:
	CDemoComDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOCOM_DIALOG };
#endif

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
	afx_msg void OnBnClickedBtnTest();
	void SetEditTExt(LPCTSTR pszText, int iPointSize, LPCTSTR szFontName,double dWidth);
private:
	CEdit m_wndEdtWrapText;

	CString m_sFontName;
	double m_dPointSize;
};
