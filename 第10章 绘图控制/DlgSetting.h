#pragma once


// CDlgSetting �Ի���

class CDlgSetting : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetting)

public:
	CDlgSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetting();

// �Ի�������
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	static UINT m_nLineWidth;
	static int m_nLineStyle;
	afx_msg void OnEnChangeEdtLinewidth();
	afx_msg void OnBnClickedRad1();
	afx_msg void OnPaint();
	COLORREF m_clr;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CBrush m_brush;
};
