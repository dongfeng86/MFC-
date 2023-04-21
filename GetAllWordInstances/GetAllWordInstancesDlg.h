
// GetAllWordInstancesDlg.h: 头文件
//

#pragma once
#include <map>

#define MAXTITLELEN 256
#define MAXCLASSLEN 256

//窗口信息结构体
struct SWinInfo
{
public:
	HWND hWnd;
	HWND hParent;
	HWND hOwner;
	LONG lStyle;
	DWORD idProcess;  // process id
	DWORD idThread;  // creator thread id
	TCHAR pszTitle[MAXTITLELEN];	//Window title
	TCHAR pszWinClass[MAXCLASSLEN];// window class name.

	void Reset() {
		hWnd = hParent = hOwner = NULL;
		idProcess = idThread = NULL;
		lStyle = 0;
		memset(pszTitle, 0, sizeof(pszTitle));
		memset(pszWinClass, 0, sizeof(pszWinClass));
	}
};

// CGetAllWordInstancesDlg 对话框
class CGetAllWordInstancesDlg : public CDialog
{
public:
	typedef std::map<CString, CString> MapDocTitle2Cont;
	typedef MapDocTitle2Cont::iterator mapIter;
	CGetAllWordInstancesDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_GETALLWORDINSTANCES_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

protected:
	void GetDocsCont(MapDocTitle2Cont& mapProcessId2String);

private:
	CListCtrl m_wndLstProcess;
	MapDocTitle2Cont m_mapProcessId2String;
	CEdit m_wndEdt;
};
