
// CustomEditDlg.h: 头文件
//

//这个工程很简单，只是想验证一个问题，
//当WM_NOTIFY发送后，控件会优先处理它。其他反射消息发出后，父窗口会优先处理它，然后控件才接收到该消息(前提是调用基类处理函数)。
//另外，EN_KILLFOCUS和WM_KILLFOCUS的区别，前者这个消息是个通告消息，包含了控件ID等信息，而后者，仅仅是控件这个窗口
//失去了焦点，是个Windows标准消息

#pragma once

class CCustomEdit :public CEdit
{
public:
	CCustomEdit();
	virtual ~CCustomEdit();
	
private:
	COLORREF m_clrText;
	COLORREF m_clrBkgnd;
	CBrush m_brBkgnd;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnEnKillfocus();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


// CCustomEditDlg 对话框
class CCustomEditDlg : public CDialog
{
// 构造
public:
	CCustomEditDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_CUSTOMEDIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
private:
	CCustomEdit m_wndEdtCustom;
	//CEdit m_wndEdtCustom;
	CBrush m_brEdtBkgnd;
public:
	afx_msg void OnEnKillfocusEdtCustom();
};
