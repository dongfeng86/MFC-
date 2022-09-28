
// CustomSpinButtonDlg.h: 头文件
//

#pragma once
#include "CSpinEdit.h"
#include "CSpinNew.h"
//#include "CCustomSpinButton.h"


// CCustomSpinButtonDlg 对话框
class CCustomSpinButtonDlg : public CDialog
{
// 构造
public:
	CCustomSpinButtonDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_CUSTOMSPINBUTTON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CCustomSpinEdit m_wndSpinEdit;
	CSpinEdit m_wndSpinEdit;
	//CSpinNew m_wndSpin;
};
