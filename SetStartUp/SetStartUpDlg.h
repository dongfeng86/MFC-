
// SetStartUpDlg.h: 头文件
//

#pragma once
#include <vector>


// CSetStartUpDlg 对话框
class CSetStartUpDlg : public CDialogEx
{
public:
	CSetStartUpDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_SETSTARTUP_DIALOG };

protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnShow();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnDelItem();
	afx_msg void OnBnClickedBtnAddStartup();
	DECLARE_MESSAGE_MAP()

private:
	void FillList();

	CListCtrl m_wndLst;
	static CString m_sPath;						//启动项的键路径
	std::vector<CString> m_arsStartItemPath;	//保持键值的名称
	std::vector<CString> m_arsStart;			//保持键值的数值
};
