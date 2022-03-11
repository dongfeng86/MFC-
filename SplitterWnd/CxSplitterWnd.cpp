#include "pch.h"
#include "CxSplitterWnd.h"


CxSplitterWnd::CxSplitterWnd()
{

}

CxSplitterWnd::~CxSplitterWnd()
{

}

BOOL CxSplitterWnd::BindWithControl(CWnd* pParent, DWORD idCtrl)
{
	m_pParent = pParent;
	m_iLeftMin = m_iRightMin = 10;

	SubclassWindow(m_pParent->GetDlgItem(idCtrl)->GetSafeHwnd());

	//确保从对话框中获得鼠标消息
	DWORD style = GetStyle();

	//这个函数没有搞清楚
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, style | SS_NOTIFY);

	return TRUE;
}

void CxSplitterWnd::Unbind()
{

}

void CxSplitterWnd::SetMinWidth(int left, int right)
{
	m_iLeftMin = left;
	m_iRightMin = right;
}

BOOL CxSplitterWnd::AttachAsLeftPane(DWORD idCtrl)
{
	m_idLeft.Add(idCtrl);
	return TRUE;
}

BOOL CxSplitterWnd::AttachAsRightPane(DWORD idCtrl)
{
	m_idRight.Add(idCtrl);
	return TRUE;
}

BOOL CxSplitterWnd::DetachAllPanes(void)
{
	m_idLeft.RemoveAll();
	m_idRight.RemoveAll();
	return TRUE;
}

void CxSplitterWnd::RecalcLayout(void)
{
	CWnd* pane;
	RECT rcBar, rcPane;

	GetWindowRect(&rcBar);
	m_pParent->ScreenToClient(&rcBar);

	int i;
	DWORD id;

	for (i = 0; i < m_idLeft.GetSize(); i++) {
		id = m_idLeft.GetAt(i);
		pane = m_pParent->GetDlgItem(id);
		pane->GetWindowRect(&rcPane);
		m_pParent->ScreenToClient(&rcPane);
		rcPane.right = rcBar.left - 1;
		pane->MoveWindow(&rcPane, FALSE);
	}

	for (i = 0; i < m_idRight.GetSize(); i++)
	{
		id = m_idRight.GetAt(i);
		pane = m_pParent->GetDlgItem(id);
		pane->GetWindowRect(&rcPane);
		m_pParent->ScreenToClient(&rcPane);
		rcPane.left = rcBar.right + 1;
		pane->MoveWindow(&rcPane, FALSE);
	}

	m_pParent->Invalidate();
}

BOOL CxSplitterWnd::GetMouseClipRect(LPRECT rcClip, CPoint point)
{
	RECT rcOrg, rcTarget, rcParent, rcPane;
	DWORD id;

	GetWindowRect(&rcOrg);
	m_pParent->GetClientRect(&rcParent);
	m_pParent->ClientToScreen(&rcParent);

	rcTarget = rcOrg;
	rcTarget.left = rcParent.left + m_iLeftMin;
	for (int i = 0; i < m_idLeft.GetSize(); i++) {
		id = m_idLeft.GetAt(i);
		m_pParent->GetDlgItem(id)->GetWindowRect(&rcPane);
		if (rcTarget.left < rcPane.left + m_iLeftMin) {
			rcTarget.left = rcPane.left + m_iLeftMin;
		}
	}

	rcTarget.right = rcParent.right - m_iRightMin;
	for (int i = 0; i < m_idRight.GetSize(); i++)
	{
		id = m_idRight.GetAt(i);
		m_pParent->GetDlgItem(id)->GetWindowRect(&rcPane);
		if (rcTarget.right > rcPane.right - m_iRightMin) {
			rcTarget.right = rcPane.right - m_iRightMin;
		}
	}

	if (rcTarget.left >= rcTarget.right) {
		TRACE(_T("No room to drag the x-splitter bar"));
		return FALSE;
	}

	rcClip->left = rcTarget.left + point.x;
	rcClip->right = rcTarget.right - (rcOrg.right - rcOrg.left - point.x) + 1;
	rcClip->top = rcOrg.top;
	rcClip->bottom = rcOrg.bottom;

	return TRUE;
}
