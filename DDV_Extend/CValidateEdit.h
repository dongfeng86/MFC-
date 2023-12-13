#ifndef _CVALIDATEEDIT_H_
#define _CVALIDATEEDIT_H_

//-----------------------------------------------------------------------------+
//=ClassName:   CValidateEdit
//=Author:      zdf
//=Description: 限制编辑框仅仅能输入整形、浮点型数值。
//=Date:        2022-10-26 
//-----------------------------------------------------------------------------+
class CValidateEdit : public CEdit
{
	DECLARE_DYNAMIC(CValidateEdit)
	enum EInputType { kInt, kDouble, kString };
public:
	CValidateEdit();
	virtual ~CValidateEdit();
	void SetEditType(EInputType eType = CValidateEdit::kDouble);
	void SetRange(double dMin, double dMax, BOOL bIncludeMin, BOOL bIncludeMax);

	//是否允许输入空
	void AllowEmpty(bool bAllowEmpty = false);
	//设置非法输入时的提示字符串
	void SetPromptMsg(LPCTSTR pszLessThanMin, LPCTSTR pszMoreThanMax,
		LPCTSTR pszInvalid, LPCTSTR pszInputEmpty);
protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEnKillfocus();
	afx_msg BOOL OnEnSetfocus();
	DECLARE_MESSAGE_MAP()
private:
	EInputType	m_eType;
	double		m_dMinValue;
	double		m_dMaxValue;
	BOOL		m_bIncludeMin, m_bIncludeMax;
	CString		m_sLastValue;

	CString		m_sPromptLessThanMin;
	CString		m_sPromptMoreThanMax;
	CString		m_sPromptInvalid;
	CString		m_sInputEmpty;
	bool		m_bAllowEmpty;
};

#endif