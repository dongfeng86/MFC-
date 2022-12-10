// CSpinEdit.cpp: 实现文件
//

#include "pch.h"
#include "CustomSpinButton.h"
#include "CSpinEdit.h"


// CSpinEdit

IMPLEMENT_DYNAMIC(CSpinEdit, CEdit)

CSpinEdit::CSpinEdit()
{

}

CSpinEdit::~CSpinEdit()
{
}


BEGIN_MESSAGE_MAP(CSpinEdit, CEdit)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int CSpinEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CSpinEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CEdit::Create(dwStyle, rect, pParentWnd, nID);
}


void CSpinEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CEdit::PreSubclassWindow();

	if (GetSafeHwnd())
	{
		CWnd* pWndParent = GetParent();
		if (m_wndSpin.Create(WS_VISIBLE | WS_CHILD | UDS_ARROWKEYS | UDS_ALIGNRIGHT | UDS_HOTTRACK | UDS_NOTHOUSANDS | UDS_SETBUDDYINT, CRect(0,0,0,0), pWndParent, 1))
		{
			m_wndSpin.SetRange(0, 10);
			m_wndSpin.SetBuddy(this);
		}
	}
}


void CSpinEdit::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
