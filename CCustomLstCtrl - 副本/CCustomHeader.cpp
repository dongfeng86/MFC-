#include "pch.h"
#include "CCustomHeader.h"

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
	::DrawFrameControl(lpDrawItemStruct->hDC,
		&lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

	UINT uFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
	//DRAW THE TEXT
	::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
		&lpDrawItemStruct->rcItem, uFormat);

	pDC->SelectObject(hOldFont);
}

BEGIN_MESSAGE_MAP(CCustomHeader, CHeaderCtrl)
END_MESSAGE_MAP()
