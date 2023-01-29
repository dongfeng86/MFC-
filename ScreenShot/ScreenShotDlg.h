
// ScreenShotDlg.h: 头文件
//

#pragma once

#define WM_MOUSEBUTTONDOWN WM_USER+777

// CScreenShotDlg 对话框
class CScreenShotDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenShotDlg)
public:
	CScreenShotDlg(CWnd* pParent = nullptr);
	enum { IDD = IDD_SCREENSHOT_DIALOG };
	bool m_bDraging;

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnScreenShot();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_bmpMemory;
	CStatic m_wndPicPreview;
	int m_nScrolHPos;
	int m_nScrolVPos;
	CScrollBar m_wndVertScroll;
	CScrollBar m_wndHorScroll;
};
