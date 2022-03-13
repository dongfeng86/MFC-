#include "pch.h"
#include "CxSplitterWnd.h"

CxSplitterWnd::CxSplitterWnd()
{}

CxSplitterWnd::~CxSplitterWnd()
{}

BOOL CxSplitterWnd::BindWithCtrl(CWnd* pParent, DWORD idCtrl)
{
	m_pParent = pParent;
	m_iLeftMin = m_iRightMin = 10;

	//子类化窗口
	SubclassWindow(m_pParent->GetDlgItem(idCtrl)->GetSafeHwnd());

	//确保控件样式包含SS_NOTIFY,确保从对话框中获得鼠标消息
	DWORD style = GetStyle();
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, style | SS_NOTIFY);

	return TRUE;
}

void CxSplitterWnd::UnbindCtrl()
{
	DetachAllPanes();
	UnsubclassWindow();
}

void CxSplitterWnd::SetMinWidth(int left, int right)
{
	m_iLeftMin = left;
	m_iRightMin = right;
}

BOOL CxSplitterWnd::AttachCtrlAsLeftPane(DWORD idCtrl)
{
	m_idLeft.Add(idCtrl);
	return TRUE;
}

BOOL CxSplitterWnd::AttachCtrlAsRightPane(DWORD idCtrl)
{
	m_idRight.Add(idCtrl);
	return TRUE;
}

BOOL CxSplitterWnd::DetachAllPanes()
{
	m_idLeft.RemoveAll();
	m_idRight.RemoveAll();
	return TRUE;
}

void CxSplitterWnd::AdjustLayout()
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

	//point指的是窗口的客户坐标，而不是屏幕坐标
	rcClip->left = rcTarget.left + point.x;
	rcClip->right = rcTarget.right - (rcOrg.right - rcOrg.left - point.x) + 1;
	rcClip->top = rcOrg.top;
	rcClip->bottom = rcOrg.bottom;

	return TRUE;
}
BEGIN_MESSAGE_MAP(CxSplitterWnd, CWnd)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


BOOL CxSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	;; SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	return TRUE;
}

void CxSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	//don't handle if capture already set
	if (::GetCapture() != NULL) return;
	
	//don't handle if no room to drag
	RECT rcMouseClip;
	if (!GetMouseClipRect(&rcMouseClip, point)) return;
	::ClipCursor(&rcMouseClip);

	// set capture to the window which received this message
	SetCapture();
	ASSERT(this == CWnd::GetCapture());

	// get DC for drawing
	CDC* pDrawDC;
	pDrawDC = m_pParent->GetDC();
	ASSERT_VALID(pDrawDC);

	int curX, curY;
	int xDiff, yDiff;
	CRect rectOrg, rectCur, rectOld;
	CSize sizeBar;

	GetWindowRect(rectOrg);
	sizeBar = CSize(rectOrg.Width(), rectOrg.Height());

	m_pParent->ScreenToClient(rectOrg);
	pDrawDC->DrawDragRect(&rectOrg, sizeBar, NULL, sizeBar);
	rectOld = rectCur = rectOrg;
	xDiff = yDiff = 0;

	// get messages unitl capture lost or cancelled/accepted
	BOOL bContinue;
	for (bContinue = TRUE; bContinue != FALSE;) {
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (CWnd::GetCapture() != this)
			break;

		switch (msg.message) 
		{
		case WM_MOUSEMOVE:
			curX = (int)(short)LOWORD(msg.lParam);
			curY = (int)(short)HIWORD(msg.lParam);

			xDiff = curX - point.x;
			yDiff = curY - point.y;

			rectCur = rectOrg;
			rectCur.left += xDiff;
			rectCur.right += xDiff;
			pDrawDC->DrawDragRect(&rectCur, sizeBar, &rectOld, sizeBar);
			rectOld = rectCur;

			TRACE(_T("\nMouse Move"));
			break;
		case WM_KEYDOWN:
			if (msg.wParam != VK_ESCAPE)
			{
				TRACE(_T("\nPress key"));
				break;
			}
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
			bContinue = FALSE;
		default:
			DispatchMessage(&msg);
			break;
		}
	}

	pDrawDC->DrawDragRect(&rectCur, sizeBar, NULL, sizeBar);
	m_pParent->ReleaseDC(pDrawDC);
	ReleaseCapture();
	::ClipCursor(NULL);

	if (xDiff == 0)
		return;

	// 移动垂直分割条
	MoveWindow(rectCur, FALSE);
	AdjustLayout();
	
	// 向父窗口发送消息
	m_pParent->SendMessage(WM_SPLITTER_HOR_MOVED, xDiff, GetDlgCtrlID());
}
