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
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	*pResult = 0;
}
