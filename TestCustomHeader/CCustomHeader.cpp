// CCustomHeader.cpp: 实现文件
//

#include "pch.h"
#include "TestCustomHeader.h"
#include "CCustomHeader.h"


// CCustomHeader

IMPLEMENT_DYNAMIC(CCustomHeader, CHeaderCtrl)

CCustomHeader::CCustomHeader()
	:m_nTextAlignFormat(DT_CENTER | DT_SINGLELINE | DT_VCENTER)
{}

CCustomHeader::~CCustomHeader()
{}

void CCustomHeader::SetTextAlign(UINT uFormat)
{
	m_nTextAlignFormat = uFormat;
}

BEGIN_MESSAGE_MAP(CCustomHeader, CHeaderCtrl)
END_MESSAGE_MAP()

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
	HGDIOBJ hOldFont = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	
	// 绘制按钮边框
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

	//绘制文本
	::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
		&lpDrawItemStruct->rcItem, m_nTextAlignFormat);

	pDC->SelectObject(hOldFont);
}