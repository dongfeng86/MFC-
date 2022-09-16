// TestBtn.cpp : 实现文件
//

#include "stdafx.h"
#include "TestBtn.h"
#include "Resource.h"

// CTestBtn

IMPLEMENT_DYNAMIC(CTestBtn, CButton)

CTestBtn::CTestBtn()
{

}

CTestBtn::~CTestBtn()
{
}


BEGIN_MESSAGE_MAP(CTestBtn, CButton)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTestBtn 消息处理程序
void CTestBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	UINT uStyle = DFCS_BUTTONPUSH;

	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;

	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
		DFC_BUTTON, uStyle);

	// Get the button's text.
	CString strText;
	GetWindowText(strText);

	//方法一，绿底红字，
	//COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
	//::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
	//	&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	//::SetTextColor(lpDrawItemStruct->hDC, crOldColor);

	//方法二，绿底红字
	CBrush bBackgroud;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	bBackgroud.CreateSolidBrush(RGB(0,255,0));
	pDC->SetBkMode(TRANSPARENT);
	//pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(RGB(255, 255, 0));
	pDC->FillRect(&lpDrawItemStruct->rcItem,&bBackgroud);

	//方法三，在控件上加入一个背景图片
	//CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP3);
	//BITMAP bmp;
	//bitmap.GetBitmap(&bmp);
	//CRect rectBtn(lpDrawItemStruct->rcItem);
	//CDC dcMemory;
	//dcMemory.CreateCompatibleDC(pDC);
	//CBitmap* pOldBitmap=dcMemory.SelectObject(&bitmap);
	//pDC->SetStretchBltMode(COLORONCOLOR);
	//pDC->StretchBlt(0,0,rectBtn.Width(),rectBtn.Height(),
	//	&dcMemory,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//dcMemory.SelectObject(pOldBitmap);

	//在控件上输出字符
	COLORREF crOldColor=pDC->SetTextColor(RGB(255,0,0));
	pDC->DrawText(strText,&lpDrawItemStruct->rcItem,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	pDC->SetTextColor(crOldColor);
}