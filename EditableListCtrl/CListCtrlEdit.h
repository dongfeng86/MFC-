#pragma once
class CListCtrlEdit	: public CListCtrl
{
public:
	CListCtrlEdit();

protected:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	CEdit m_wndEdt;
	int m_iCurRow;
	int m_iCurColunm;

};

