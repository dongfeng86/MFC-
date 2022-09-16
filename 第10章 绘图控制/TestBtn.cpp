// TestBtn.cpp : ʵ���ļ�
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

// CTestBtn ��Ϣ�������
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

	//����һ���̵׺��֣�
	//COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
	//::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
	//	&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	//::SetTextColor(lpDrawItemStruct->hDC, crOldColor);

	//���������̵׺���
	CBrush bBackgroud;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	bBackgroud.CreateSolidBrush(RGB(0,255,0));
	pDC->SetBkMode(TRANSPARENT);
	//pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(RGB(255, 255, 0));
	pDC->FillRect(&lpDrawItemStruct->rcItem,&bBackgroud);

	//���������ڿؼ��ϼ���һ������ͼƬ
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

	//�ڿؼ�������ַ�
	COLORREF crOldColor=pDC->SetTextColor(RGB(255,0,0));
	pDC->DrawText(strText,&lpDrawItemStruct->rcItem,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	pDC->SetTextColor(crOldColor);
}