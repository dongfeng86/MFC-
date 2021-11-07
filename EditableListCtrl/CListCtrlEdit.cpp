#include "pch.h"
#include "CListCtrlEdit.h"

CListCtrlEdit::CListCtrlEdit()
	:m_iCurColunm(-1)
	,m_iCurRow(-1)
{

}
BEGIN_MESSAGE_MAP(CListCtrlEdit, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CListCtrlEdit::OnNMClick)
END_MESSAGE_MAP()


void CListCtrlEdit::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	*pResult = 0;
}
