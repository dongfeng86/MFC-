
// ChatDlg.h: 头文件
//

#pragma once

#define WM_RECVDATA WM_USER+1

struct SRecvParam
{
	SOCKET sock;
	HWND hwnd;
};

// CChatDlg 对话框
class CChatDlg : public CDialogEx
{
public:
	CChatDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_CHAT_DIALOG };

protected:
	BOOL InitSocket();

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	SOCKET m_socket;
public:
	afx_msg void OnBnClickedBtnSend();
private:
	CIPAddressCtrl m_wndIPCtrl;
};
