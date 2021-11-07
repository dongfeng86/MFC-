#include "StdAfx.h"
#include "MyButton.h"

CMyButton::CMyButton(UINT idBmpNormal,UINT idBmpPress,UINT idBmpHover,UINT idBmpFocus)
	:m_bTrackMouseEvent(true)
	,m_bHover(false)
{
	m_bmpNormal.LoadBitmap(idBmpNormal);
	m_bmpPress.LoadBitmap(idBmpPress);
	m_bmpHover.LoadBitmap(idBmpHover);
	m_bmpFocus.LoadBitmap(idBmpFocus);
}

CMyButton::~CMyButton(void)
{
}

void CMyButton::SetBmpId(UINT idBmpNormal,UINT idBmpPress,UINT idBmpHover,UINT idBmpFocus)
{
	//�˴�ע�⣬CBitmap��μ���λͼ������ᱨ��
	if(m_bmpNormal.m_hObject)
		m_bmpNormal.DeleteObject();	
	if(m_bmpPress.m_hObject)
		m_bmpPress.DeleteObject();
	if(m_bmpFocus.m_hObject)
		m_bmpFocus.DeleteObject();
	if(m_bmpHover.m_hObject)
		m_bmpHover.DeleteObject();

	m_bmpNormal.LoadBitmap(idBmpNormal);
	m_bmpPress.LoadBitmap(idBmpPress);
	m_bmpFocus.LoadBitmap(idBmpFocus);
	m_bmpHover.LoadBitmap(idBmpHover);	
}

BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bTrackMouseEvent)
	{
		TRACKMOUSEEVENT cTrackEvent;
		cTrackEvent.cbSize=sizeof(TRACKMOUSEEVENT);
		cTrackEvent.dwFlags=TME_HOVER|TME_LEAVE;
		cTrackEvent.dwHoverTime=10;
		cTrackEvent.hwndTrack=GetSafeHwnd();
		if(::_TrackMouseEvent(&cTrackEvent))	//�������ʧ�ܣ����ٸ�������¼�
			m_bTrackMouseEvent=false;
	}

	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnMouseLeave()
{
	m_bHover=false;
	m_bTrackMouseEvent=true;	//���¿�ʼ����
	Invalidate();				//�ػ水ť
	
	CButton::OnMouseLeave();
}

void CMyButton::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bTrackMouseEvent=false;	//���ٸ��٣���Ϊ�Ѿ��ڿؼ���Χ����
	m_bHover=true;
	Invalidate();				//�ػ水ť
	CButton::OnMouseHover(nFlags, point);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect=lpDrawItemStruct->rcItem;
	CDC* pDc=CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDc=pDc->SaveDC();

	CBitmap* pBmp=NULL;
	if(lpDrawItemStruct->itemState & ODS_SELECTED)	//ѡ��
	{
		pBmp=&m_bmpPress;
	}
	else if(lpDrawItemStruct->itemState & ODS_FOCUS)	//����
	{
		pBmp=&m_bmpFocus;
	}
	else if(m_bHover)	//ͣ��
	{
		pBmp=&m_bmpHover;
	}
	else				//����
		pBmp=&m_bmpNormal;

	if(pBmp->m_hObject)
	{
		BITMAP bmp;
		pBmp->GetBitmap(&bmp);
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(pDc);
		dcCompatible.SelectObject(pBmp);
		pDc->StretchBlt(0,0,rect.Width(),rect.Height(),
			&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	}

	pDc->RestoreDC(nSaveDc);
}
