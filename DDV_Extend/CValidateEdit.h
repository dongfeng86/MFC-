#pragma once


// CValidateEdit

class CValidateEdit : public CEdit
{
	DECLARE_DYNAMIC(CValidateEdit)
	enum EInputType{ kInt, kDouble, kString };
public:
	CValidateEdit();
	virtual ~CValidateEdit();
	void SetEditType(EInputType eType);
	void SetRange(double dMin, double dMax,BOOL bApplyMin,BOOL bApplyMax);

protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEnKillfocus();
	afx_msg BOOL OnEnSetfocus();
	DECLARE_MESSAGE_MAP()
private:
	EInputType	m_eType;
	double		m_dMin, m_dMax;
	BOOL		m_bApplyMin, m_bApplyMax;
	CString		m_sLastValue;
};


