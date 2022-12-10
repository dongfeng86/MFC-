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


//����ΪCCustomListCtrlʵ��
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

	//���ı����� 
	CRect bgRect = lpDrawItemStruct->rcItem;
	if (bSelect)//����ѡ����ɫ
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	}

	//�����ı�
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		//ѭ������
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

	//���е�����⣬����ṹ�Ѿ�����չΪ�ܹ���Ӧ����ĵ�����⡣
	LVHITTESTINFO cHitTest;
	cHitTest.pt = pNMItemActivate->ptAction;
	if (-1 != SubItemHitTest(&cHitTest))	//����������λ���ĸ���Ԫ����
	{
		if (cHitTest.flags & LVHT_ONITEMLABEL)
		{
			m_posCell.iXPos = cHitTest.iItem;
			m_posCell.iYPos = cHitTest.iSubItem;
			//�жϵ�Ԫ���Ƿ�ɱ༭
			std::map<SCellPostion, SCellDropListInfo>::iterator it;
			it = m_mapCellPosToInfo.find(m_posCell);
			if (it != m_mapCellPosToInfo.end())
			{
				CRect rect;	//��Ԫ��ĳߴ�
				GetSubItemRect(m_posCell.iXPos, m_posCell.iYPos, LVIR_LABEL, rect);
				CString sCellCont = GetItemText(m_posCell.iXPos, m_posCell.iYPos);
				
				if (it->second.arListString.size())
				{
					//�����б��
					if (!m_wndCmbTemp.m_hWnd)
					{
						m_wndCmbTemp.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN, rect, this, _ID_DYN_CREATE_EDIT_);
						m_wndCmbTemp.SetFont(GetFont(), FALSE);		//�������壬�����б�����岻��
					}
					m_wndCmbTemp.ResetContent();
					m_wndCmbTemp.SetWindowText(sCellCont);
					m_wndCmbTemp.MoveWindow(rect);
					m_wndCmbTemp.ShowWindow(SW_SHOW);

					//������ԶԻ�����ʽ��ʾ
					if (!(it->second.pDlg))
					{
						for (int j = 0; j < it->second.arListString.size(); j++)
							m_wndCmbTemp.AddString(it->second.arListString[j]);
					}

					m_wndCmbTemp.SetFocus();
				}
				else
				{
					//�����༭��
					if (!m_wndEdtTemp.m_hWnd)
					{
						m_wndEdtTemp.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rect, this, _ID_DYN_CREATE_EDIT_ + 1);
						m_wndEdtTemp.SetFont(GetFont(), FALSE);
					}
					//m_wndEdtTemp.ModifyStyleEx(WS_EX_LEFT, WS_EX_RIGHT);
					m_wndEdtTemp.SetWindowText(sCellCont);
					m_wndEdtTemp.MoveWindow(rect);
					m_wndEdtTemp.ShowWindow(SW_SHOW);
					m_wndEdtTemp.SetSel(0, sCellCont.GetLength(), FALSE);	//���ù��ѡ����������
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
	// TODO: �ڴ����ר�ô����/����û���

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
