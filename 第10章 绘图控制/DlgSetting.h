#pragma once
#include "sxbtn.h"
#include "TestBtn.h"
#include "SXBtn.h"
#include "afxwin.h"



class CCustomBmpBtn:public CButton
{
	DECLARE_DYNAMIC(CCustomBmpBtn)

public:
	CCustomBmpBtn();
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bOver;		//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	bool m_bTrackingMouse;
	CBitmap m_bmpNormal;	// ���س�ʼ״̬ͼƬ
	CBitmap m_bmpPress;		// ����״̬
	CBitmap m_bmpFocus;
	CBitmap m_bmpHover;
};


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
	CFont m_font;
	CTestBtn m_wndTestBtn;
public:
	CSXBtn m_wndCancel;
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CCustomBmpBtn m_wndTestBad;
	//CButton m_wndTestBad;
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
