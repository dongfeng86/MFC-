#include "stdafx.h"
#include "CCustomListCtrl.h"
#include <winuser.h>

#define _ID_DYN_CREATE_COMBO_ 10000
#define _ID_DYN_CREATE_EDIT_ (_ID_DYN_CREATE_COMBO_ + 1)
#define _ID_DYN_CREATE_BUTTON_ (_ID_DYN_CREATE_COMBO_ + 2)
#define _ID_DYN_CREATE_EDIT_FOR_BUTTON_ (_ID_DYN_CREATE_COMBO_ + 3)

//����ΪCCustomHeaderʵ��
//

IMPLEMENT_DYNAMIC(CCustomHeader, CHeaderCtrl)

CCustomHeader::CCustomHeader()
	:m_nTextAlignFormat(DT_CENTER | DT_SINGLELINE | DT_VCENTER)
{}

void CCustomHeader::SetTextAlign(UINT uFormat)
{
	m_nTextAlignFormat = uFormat;
}

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

	//DRAW THE TEXT
	::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
		&lpDrawItemStruct->rcItem, m_nTextAlignFormat);

	pDC->SelectObject(hOldFont);
}

BEGIN_MESSAGE_MAP(CCustomHeader, CHeaderCtrl)
END_MESSAGE_MAP()


//����ΪCCustomListCtrlʵ��
//

IMPLEMENT_DYNAMIC(CCustomListCtrl, CListCtrl)

CCustomListCtrl::CCustomListCtrl()
	:m_pDialog(NULL)
	,m_uRowHeight(22)
	,m_posCell(0,0)
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
	ON_CBN_SELCHANGE(_ID_DYN_CREATE_COMBO_, OnCellSelectItem)
	ON_CBN_KILLFOCUS(_ID_DYN_CREATE_COMBO_, OnComboKillFocs)
	ON_EN_KILLFOCUS(_ID_DYN_CREATE_EDIT_, OnEditKillFocs)
	ON_EN_KILLFOCUS(_ID_DYN_CREATE_EDIT_FOR_BUTTON_, OnEditForButtonKillFocs)
	ON_BN_CLICKED(_ID_DYN_CREATE_BUTTON_,OnBtnClick)
END_MESSAGE_MAP()

void CCustomListCtrl::DrawItem(LPDRAWITEMSTRUCT  lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	COLORREF crOldTextColor = pDC->GetTextColor();
	COLORREF crOldBkColor = pDC->GetBkColor();

	LVITEM lvi = { 0 };
	lvi.mask = LVIF_STATE;
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
	
	LVHITTESTINFO cHitTest;	
	cHitTest.pt = pNMItemActivate->ptAction;//���е������
	if (-1 != SubItemHitTest(&cHitTest))	//����������λ���ĸ���Ԫ����
	{
		if (cHitTest.flags & LVHT_ONITEMLABEL)
		{
			m_posCell.iItem = cHitTest.iItem;
			m_posCell.iSubItem = cHitTest.iSubItem;

			std::map<SCellPostion, SCellDropListInfo>::iterator it;
			it = m_mapCellPosToInfo.find(m_posCell);
			if (it != m_mapCellPosToInfo.end())
			{
				CRect rect;	//��Ԫ��ĳߴ�
				GetSubItemRect(m_posCell.iItem, m_posCell.iSubItem, LVIR_LABEL, rect);
				//����ǵ�һ�У�Ҫ���⴦��
				if (!m_posCell.iSubItem)
					rect.left = 0;
				CString sCellCont = GetItemText(m_posCell.iItem, m_posCell.iSubItem);
				
				if (it->second.IsCombo()) //�����б��
				{
					if (!m_wndCmbTemp.m_hWnd)
					{
						m_wndCmbTemp.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN, rect,
							this, _ID_DYN_CREATE_COMBO_);
						m_wndCmbTemp.SetFont(GetFont(), FALSE);		//�������壬�����б�����岻��
					}
					m_wndCmbTemp.ResetContent();
					m_wndCmbTemp.ShowWindow(SW_SHOW);
					m_wndCmbTemp.SetWindowText(sCellCont);
					//rect.bottom += 50;
					m_wndCmbTemp.MoveWindow(rect);

					int iWidth = ::GetSystemMetrics(SM_CYBORDER);
					m_wndCmbTemp.SetItemHeight(-1, rect.Height() - 5 * iWidth);	//����ط�����5����
					//m_wndCmbTemp.SetItemHeight(-1, 30);

					for (int j = 0; j < it->second.arListString.size(); j++)
						m_wndCmbTemp.AddString(it->second.arListString[j]);
					m_wndCmbTemp.SetFocus();
				}
				else if (it->second.IsEditCell()) //�����༭��
				{
					if (!m_wndEdtTemp.m_hWnd)
					{
						m_wndEdtTemp.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rect, this, 
							_ID_DYN_CREATE_EDIT_);
						m_wndEdtTemp.SetFont(GetFont(), FALSE);
					}
					m_wndEdtTemp.ShowWindow(SW_SHOW);
					m_wndEdtTemp.SetWindowText(sCellCont);
					m_wndEdtTemp.MoveWindow(rect);
					m_wndEdtTemp.SetSel(0, sCellCont.GetLength(), FALSE);	//���ù��ѡ����������
					m_wndEdtTemp.SetFocus();
				}
				else  //�ڵ�Ԫ���Ҳഴ��һ����ť
				{
					if (it->second.pDlg->GetRuntimeClass() == CDlgAreaCondition::GetThisClass())
					{
						m_pDialog = (CDlgAreaCondition*)it->second.pDlg;
						CString sItem = m_pDialog->GetCheckItem();
						SetItemText(m_posCell.iItem, m_posCell.iSubItem, sItem);
					}
					else
						m_pDialog = NULL;


					//���ȴ����༭��
					if (!m_wndEdtForBtn.m_hWnd)
					{
						m_wndEdtForBtn.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rect, this,
							_ID_DYN_CREATE_EDIT_FOR_BUTTON_);
						m_wndEdtForBtn.SetFont(GetFont(), FALSE);
					}
					m_wndEdtForBtn.ShowWindow(SW_SHOW);
					m_wndEdtForBtn.SetWindowText(sCellCont);
					CRect rectEdt(rect);
					rectEdt.right = rectEdt.right - rect.Height();
					m_wndEdtForBtn.MoveWindow(rectEdt);
					m_wndEdtForBtn.SetSel(0, sCellCont.GetLength(), FALSE);	//���ù��ѡ����������

					//Ȼ�󴴽��Ҳ�λͼ��ť
					rectEdt = rect;
					rectEdt.left = rectEdt.right - rect.Height();
					if (!m_wndBtnTemp.m_hWnd)
					{
						m_wndBtnTemp.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectEdt,
							this, _ID_DYN_CREATE_BUTTON_);
						m_wndBtnTemp.SetFont(GetFont(), FALSE);
					}
					m_wndBtnTemp.ShowWindow(SW_SHOW);
					m_wndBtnTemp.MoveWindow(rectEdt);
					m_wndEdtForBtn.SetFocus();
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
		SetItemText(m_posCell.iItem, m_posCell.iSubItem, sItem);
	}
}

void CCustomListCtrl::OnEditKillFocs(void)
{
	CString sItem;
	m_wndEdtTemp.GetWindowText(sItem);
	SetItemText(m_posCell.iItem, m_posCell.iSubItem, sItem);
	m_wndEdtTemp.ShowWindow(SW_HIDE);
}

void CCustomListCtrl::OnEditForButtonKillFocs(void)
{
	CString sItem;
	m_wndEdtForBtn.GetWindowText(sItem);
	SetItemText(m_posCell.iItem, m_posCell.iSubItem, sItem);
	m_wndEdtForBtn.ShowWindow(SW_HIDE);

	//�ж��û����λ��
	CPoint point;
	CRect rect;
	GetCursorPos(&point);
	ScreenToClient(&point);
	m_wndBtnTemp.GetWindowRect(rect);
	ScreenToClient(&rect);
	if (PtInRect(&rect, point))
		m_wndBtnTemp.ShowWindow(SW_SHOW);
	else
		m_wndBtnTemp.ShowWindow(SW_HIDE);
}

void CCustomListCtrl::OnBtnClick(void)
{
	if (m_pDialog)
	{
		//��ȡ��ǰ��Ԫ�񵥻���Ϊ��Ϣ
		std::map<SCellPostion, SCellDropListInfo>::iterator it;
		it = m_mapCellPosToInfo.find(m_posCell);
		if (it != m_mapCellPosToInfo.end())
		{
			m_pDialog->SetCheckItemList(it->second.arListString);
			if (IDOK == m_pDialog->DoModal())
			{
				CString sItem = m_pDialog->GetCheckItem();
				m_wndEdtForBtn.SetWindowText(sItem);
			}

			m_wndEdtForBtn.ShowWindow(SW_SHOW);
			m_wndEdtForBtn.SetSel(0, -1);
			m_wndEdtForBtn.SetFocus();
		}
	}
}

void CCustomListCtrl::OnComboKillFocs(void)
{
	m_wndCmbTemp.ShowWindow(SW_HIDE);
}
