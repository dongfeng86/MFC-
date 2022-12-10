#include "pch.h"
#include "CCustomListCtrl.h"
#include <winuser.h>

#define _ID_DYN_CREATE_EDIT_ 10000

IMPLEMENT_DYNAMIC(CCustomHeader, CHeaderCtrl)

CCustomHeader::CCustomHeader()
{}

void CCustomHeader::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_HEADER);
	HDITEM hdi;
	TCHAR  lpBuffer[256];

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;

	GetItem(lpDrawItemStruct->itemID, &hdi);


	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//THIS FONT IS ONLY FOR DRAWING AS LONG AS WE DON'T DO A SetFont(...)
	HGDIOBJ hOldFont = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

	UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
	//DRAW THE TEXT
	::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
		&lpDrawItemStruct->rcItem, uFormat);

	pDC->SelectObject(hOldFont);
}

BEGIN_MESSAGE_MAP(CCustomHeader, CHeaderCtrl)
END_MESSAGE_MAP()


//以下为CCustomListCtrl实现
//

IMPLEMENT_DYNAMIC(CCustomListCtrl, CListCtrl)

CCustomListCtrl::CCustomListCtrl()
{}

void CCustomListCtrl::SetRowHeigt(int nHeight)
{
	m_uRowHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CCustomListCtrl::SetCellDropList(int iItem, int iSubItem, const std::vector<CString>& arListString, CDialog* pDlg)
{
	SCellPostion pos(iItem, iSubItem);
	SCellDropListInfo info;
	info.arListString = arListString;
	info.pDlg = pDlg;
	m_mapCellPosToInfo[pos] = info;
}

BEGIN_MESSAGE_MAP(CCustomListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CCustomListCtrl::OnNMClick)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_CBN_SELCHANGE(_ID_DYN_CREATE_EDIT_, OnCellSelectItem)
	ON_CBN_KILLFOCUS(_ID_DYN_CREATE_EDIT_, OnComboKillFocs)
	ON_EN_KILLFOCUS(_ID_DYN_CREATE_EDIT_ + 1, OnEditKillFocs)
	//ON_CBN_DROPDOWN(_ID_DYN_CREATE_EDIT_, OnDropDown)
END_MESSAGE_MAP()

void CCustomListCtrl::DrawItem(LPDRAWITEMSTRUCT  lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = pDC->GetTextColor();
	COLORREF crOldBkColor = pDC->GetBkColor();

	LVITEM lvi = { 0 };
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	lvi.iItem = lpDrawItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);

	BOOL bSelect = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED)
		&& ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));

	//画文本背景 
	CRect bgRect = lpDrawItemStruct->rcItem;
	if (bSelect)//设置选中颜色
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	}

	//绘制文本
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		//循环处理
		CString szText;
		for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
		{
			CRect rcItem;
			if (!GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem))
				continue;

			szText = GetItemText(lpDrawItemStruct->itemID, i);
			rcItem.left += 5; rcItem.right -= 1;
			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
		}
	}

	// Reset the background color and the text color back to their
	// original values.
	pDC->SetTextColor(crOldTextColor);
	pDC->SetBkColor(crOldBkColor);
}

BOOL CCustomListCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

void CCustomListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	//进行单击检测，这个结构已经被扩展为能够适应子项的单击检测。
	LVHITTESTINFO cHitTest;
	cHitTest.pt = pNMItemActivate->ptAction;
	if (-1 != SubItemHitTest(&cHitTest))	//检测给定坐标位于哪个单元格上
	{
		if (cHitTest.flags & LVHT_ONITEMLABEL)
		{
			m_posCell.iXPos = cHitTest.iItem;
			m_posCell.iYPos = cHitTest.iSubItem;
			//判断单元格是否可编辑
			std::map<SCellPostion, SCellDropListInfo>::iterator it;
			it = m_mapCellPosToInfo.find(m_posCell);
			if (it != m_mapCellPosToInfo.end())
			{
				CRect rect;	//单元格的尺寸
				GetSubItemRect(m_posCell.iXPos, m_posCell.iYPos, LVIR_LABEL, rect);
				CString sCellCont = GetItemText(m_posCell.iXPos, m_posCell.iYPos);
				
				if (it->second.arListString.size())
				{
					//创建列表框
					if (!m_wndCmbTemp.m_hWnd)
					{
						m_wndCmbTemp.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN, rect, this, _ID_DYN_CREATE_EDIT_);
						m_wndCmbTemp.SetFont(GetFont(), FALSE);		//设置字体，否则列表框字体不对
					}
					m_wndCmbTemp.ResetContent();
					m_wndCmbTemp.SetWindowText(sCellCont);
					m_wndCmbTemp.MoveWindow(rect);
					m_wndCmbTemp.ShowWindow(SW_SHOW);

					//如果不以对话框形式显示
					if (!(it->second.pDlg))
					{
						for (int j = 0; j < it->second.arListString.size(); j++)
							m_wndCmbTemp.AddString(it->second.arListString[j]);
					}

					m_wndCmbTemp.SetFocus();
				}
				else
				{
					//创建编辑框
					if (!m_wndEdtTemp.m_hWnd)
					{
						m_wndEdtTemp.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rect, this, _ID_DYN_CREATE_EDIT_ + 1);
						m_wndEdtTemp.SetFont(GetFont(), FALSE);
					}
					//m_wndEdtTemp.ModifyStyleEx(WS_EX_LEFT, WS_EX_RIGHT);
					m_wndEdtTemp.SetWindowText(sCellCont);
					m_wndEdtTemp.MoveWindow(rect);
					m_wndEdtTemp.ShowWindow(SW_SHOW);
					m_wndEdtTemp.SetSel(0, sCellCont.GetLength(), FALSE);	//设置光标选中所有文字
					m_wndEdtTemp.SetFocus();
				}
			}		
		}
	}

}

void CCustomListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CCustomListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = m_uRowHeight;
}

void CCustomListCtrl::OnCellSelectItem(void)
{
	int nIndex = m_wndCmbTemp.GetCurSel();
	int nCount = m_wndCmbTemp.GetCount();
	if ((nIndex != CB_ERR) && (nCount > 1))
	{
		m_wndCmbTemp.SetCurSel(nIndex);
		CString sItem;
		m_wndCmbTemp.GetLBText(nIndex, sItem);
		SetItemText(m_posCell.iXPos, m_posCell.iYPos, sItem);
	}
}

void CCustomListCtrl::OnEditKillFocs(void)
{
	m_wndEdtTemp.ShowWindow(SW_HIDE);
}

//void CCustomListCtrl::OnDropDown(void)
//{
//	std::map<SCellPostion, SCellDropListInfo>::iterator it;
//	it = m_mapCellPosToInfo.find(m_posCell);
//	if (it != m_mapCellPosToInfo.end())
//	{
//		if (it->second.pDlg)
//		{
//			m_wndCmbTemp.ShowDropDown(FALSE);
//
//			MessageBox(_T("hello"));
//
//			::PostMessage(m_wndCmbTemp.m_hWnd, WM_COMMAND, MAKEWPARAM(m_wndCmbTemp.GetDlgCtrlID(), CBN_CLOSEUP), (LPARAM)m_wndCmbTemp.m_hWnd);
//		}
//	}
//}

void CCustomListCtrl::OnComboKillFocs(void)
{
	m_wndCmbTemp.ShowWindow(SW_HIDE);
}

BOOL CCustomListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_COMMAND)
	{
		if (m_wndCmbTemp.m_hWnd)
		{
			WPARAM wParam = pMsg->wParam;
			int id = LOWORD(wParam);
			int iNotity = HIWORD(wParam);
			TRACE(_T("id=%d,iNotify=%d"), id, iNotity);

				//std::map<SCellPostion, SCellDropListInfo>::iterator it;
				//it = m_mapCellPosToInfo.find(m_uRowHeight);
				//if (it != m_mapCellPosToInfo.end())
				//{
				//	if (it->second.pDlg)
				//	{
				//		m_wndCmbTemp.ShowDropDown(FALSE);

				//		MessageBox(_T("hello"));
				//		return TRUE;
				//	}
				//}
		}
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}
