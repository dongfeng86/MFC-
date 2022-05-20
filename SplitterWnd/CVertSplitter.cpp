#include "pch.h"
#include "CVertSplitter.h"

IMPLEMENT_DYNAMIC(CVertSplitter, CStatic)

CVertSplitter::CVertSplitter()
	:CStatic()
	, m_pParent(NULL)
	, m_iLeftMin(10)
	, m_iRightMin(10)
{}

CVertSplitter::~CVertSplitter()
{}

void CVertSplitter::SetMinWidth(int left, int right)
{
	m_iLeftMin = left;
	m_iRightMin = right;
}

BOOL CVertSplitter::AttachCtrlAsLeftPane(DWORD idCtrl)
{
	m_idLeft.Add(idCtrl);
	return TRUE;
}

BOOL CVertSplitter::AttachCtrlAsRightPane(DWORD idCtrl)
{
	m_idRight.Add(idCtrl);
	return TRUE;
}

BOOL CVertSplitter::DetachAllPanes()
{
	m_idLeft.RemoveAll();
	m_idRight.RemoveAll();
	return TRUE;
}

void CVertSplitter::AdjustLayout()
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

BEGIN_MESSAGE_MAP(CVertSplitter, CStatic)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


BOOL CVertSplitter::GetMouseClipRect(LPRECT rcClip, CPoint point)
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

	//point指的是窗口的客户坐标，而不是屏幕坐标
	rcClip->left = rcTarget.left + point.x;
	rcClip->right = rcTarget.right - (rcOrg.right - rcOrg.left - point.x) + 1;
	rcClip->top = rcOrg.top;
	rcClip->bottom = rcOrg.bottom;

	return TRUE;
}

BOOL CVertSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//以下非常奇怪，用全局函数可以，但是用CStatic方法却不行
	//if (GetCursor() == NULL)
	//	SetCursor(::LoadCursor(NULL, IDC_HELP));
	::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
	return TRUE;
}

void CVertSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	//如果鼠标被别的程序捕获，不再处理此消息
	if (::GetCapture() != NULL) return;
	m_pParent = GetParent();
	if (!m_pParent) return;

	//ClipCursor限定鼠标移动范围 
	CRect rcMouseClip;
	if (!GetMouseClipRect(rcMouseClip, point)) return;
	::ClipCursor(&rcMouseClip);

	m_pPointStart = point;

	SetCapture();	//捕获鼠标输入
	GetWindowRect(m_rcOrgRect);
	m_pParent->ScreenToClient(m_rcOrgRect);
	CDC* pDrawDC = NULL;
	pDrawDC = m_pParent->GetDC();

	pDrawDC->DrawDragRect(m_rcOrgRect, CSize(1, 1), NULL, CSize(1, 1));
	m_rcOldRect = m_rcOrgRect;

	m_pParent->ReleaseDC(pDrawDC);
}

void CVertSplitter::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GetCapture() == this)
	{
		CDC* pDrawDC = NULL;
		pDrawDC = m_pParent->GetDC();

		CRect rcCur = m_rcOrgRect;
		long xDiff = 0, yDiff = 0;
		xDiff = point.x - m_pPointStart.x;
		yDiff = point.y - m_pPointStart.y;
		rcCur.OffsetRect(xDiff, 0);
		pDrawDC->DrawDragRect(rcCur, CSize(1, 1), &m_rcOldRect, CSize(1, 1));
		m_rcOldRect = rcCur;

		m_pParent->ReleaseDC(pDrawDC);
	}
}

void CVertSplitter::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture() == this)
	{
		CDC* pDrawDC = NULL;
		pDrawDC = m_pParent->GetDC();  //获取DC

		//可以采用下列两种方式之一
		//pDrawDC->DrawDragRect(m_rcOldRect, CSize(1, 1), NULL, CSize(1, 1));
		pDrawDC->DrawDragRect(CRect(0, 0, 0, 0), CSize(1, 1), m_rcOldRect, CSize(1, 1));
		m_pParent->ReleaseDC(pDrawDC);
		::ReleaseCapture();

		MoveWindow(m_rcOldRect);
		AdjustLayout();
	}
	::ClipCursor(NULL);
}