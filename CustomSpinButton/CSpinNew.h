#pragma once


// CSpinNew

class CSpinNew : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(CSpinNew)

public:
	CSpinNew();
	virtual ~CSpinNew();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PreSubclassWindow();
};


