
// CustomComboBoxDlg.h: 头文件
//

#pragma once

class CCustomComboBox :public CComboBox
{
	DECLARE_DYNAMIC(CCustomComboBox)

public:
	CCustomComboBox();
	~CCustomComboBox();

//protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};


// CCustomComboBoxDlg 对话框
class CCustomComboBoxDlg : public CDialog
{
// 构造
public:
	CCustomComboBoxDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_CUSTOMCOMBOBOX_DIALOG };

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
private:
	CCustomComboBox m_wndCmbCustom;
public:
	afx_msg void OnCbnKillfocusCombo1();
	afx_msg void OnCbnSelchangeCombo1();
};
