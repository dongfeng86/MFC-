#pragma once


// CSpinEdit

class CSpinEdit : public CEdit
{
	DECLARE_DYNAMIC(CSpinEdit)

public:
	CSpinEdit();
	virtual ~CSpinEdit();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual void PreSubclassWindow();

private:
	CSpinButtonCtrl m_wndSpin;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


