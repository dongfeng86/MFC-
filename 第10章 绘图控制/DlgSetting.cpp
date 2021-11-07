// DlgSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "Graphic.h"

#include "DlgSetting.h"

UINT CDlgSetting::m_nLineWidth = 0;
int CDlgSetting::m_nLineStyle = 0;

IMPLEMENT_DYNAMIC(CDlgSetting, CDialog)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{
	m_clr=RGB(255,0,0);
	m_brush.CreateSolidBrush(RGB(0,0,255));
	m_font.CreatePointFont(200,_T("�����п�"));
}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LINEWIDTH, m_nLineWidth);
	DDX_Radio(pDX, IDC_RAD_1, m_nLineStyle);
	DDX_Control(pDX, IDOK, m_wndTestBtn);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Control(pDX, IDC_TEST_BAD, m_wndTestBad);
}

BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	ON_EN_CHANGE(IDC_EDT_LINEWIDTH, &CDlgSetting::OnEnChangeEdtLinewidth)
	ON_BN_CLICKED(IDC_RAD_1, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_2, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_3, &CDlgSetting::OnBnClickedRad1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgSetting ��Ϣ�������

void CDlgSetting::OnEnChangeEdtLinewidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}

void CDlgSetting::OnBnClickedRad1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
}

void CDlgSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(&dc);
	dcCompatible.SelectObject(&bitmap);

	GetClientRect(&rect);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
		0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);


	UpdateData();
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);
	dc.SelectObject(&pen);
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);

	//InvalidateRect(&rect);
}

//��θ��Ŀؼ��ı�������ɫ��ע�⣬���ַ������ܸı䰴ť�ؼ��ı�������ɫ��
HBRUSH CDlgSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(pWnd->GetDlgCtrlID()==IDC_LINESTYLE)
	{
		//�����飬��������Ч
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID()==IDC_EDT_LINEWIDTH)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(0,255,0)); //���ַ�ʽ������
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID()==IDC_TEXT)
	{
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(RGB(255,0,0));

	}
	//if(pWnd->GetDlgCtrlID()==IDOK)
	//{
	//	pDC->SetTextColor(RGB(255,0,0));

	//	return m_brush;
	//}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//����֤�����ַ��������⣬��������󱳾�ͼƬʧ��
//BOOL CDlgSetting::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CBitmap bitmap;
//	bitmap.LoadBitmap(IDB_BITMAP1);
//	BITMAP bmp;
//	bitmap.GetBitmap(&bmp);
//	CDC dcCompatible;
//	dcCompatible.CreateCompatibleDC(pDC);
//	dcCompatible.SelectObject(&bitmap);
//
//	CRect rect;
//	GetClientRect(&rect);
//	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
//	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
//		0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
//
//	return TRUE;
//	//return CDialog::OnEraseBkgnd(pDC);
//}

BOOL CDlgSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���´�����ʾ����������ť�����ͼƬ������ʾһ����

	//CBitmap bmp;
	//bmp.LoadBitmap(IDB_BITMAP3);
	//HBITMAP hBmp;
	//hBmp=(HBITMAP)bmp.Detach();
	//m_wndTestBad.LoadBitmaps(IDB_BITMAP_NORMAL,IDB_BITMAP_CLICK,IDB_BITMAP_HUNG);
	//m_wndTestBad.SizeToContent(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSetting::OnMouseMove(UINT nFlags, CPoint point)
{
	//SetFocus();


	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//POINT pt;
	//GetCursorPos(&pt);
	//CWnd* hWnd=NULL;
	//ScreenToClient(&pt);
	//hWnd=ChildWindowFromPoint(pt);
	//CWnd* pWnd2=GetDlgItem(IDC_BTN_NEW);
	//if(hWnd==pWnd2)
	//{
	//	MessageBox(_T("���������λ��\n"));
	//	if(GetFocus()!=pWnd2)
	//		pWnd2->SetFocus();
	//}
	//else
	//{
	//	if(GetFocus()==pWnd2)
	//		pWnd2->PostMessage(WM_KILLFOCUS, 0, 0);
	//}

	//CRect rect;
	//GetDlgItem(IDC_btn_testtest)->GetWindowRect(rect);
	//ScreenToClient(rect);
	//if(rect.PtInRect(point))
	//{
	//	MessageBox(_T("���������λ��\n"));
	//}

	//CRect rect;
	//GetClientRect(&rect);         //ͼƬ�ľ���
	//if(rect.PtInRect(point))
	//{

	//	//Mouse have in the rectangle.
	//	//To add your process code...
	//}
	//else
	//{
	//	//Mouse have leave the rectangle.
	//	//To add your process code...
	//}

		//POINT p;
		//GetCursorPos(&p);
		//CWnd *hwnd;
		//hwnd = WindowFromPoint(p);//���������а����ƶ��ĵ㣻�����ָ����Ļ��������Ļ�ϵ�һ���㡣
		//CWnd *hwnd2=GetDlgItem(IDC_BUTTON2);
		//if (hwnd2==hwnd)//�������ڰ�ť��
		//{
		//	if (GetFocus()!=hwnd2)//�����ť�޽��㣬��ô���ý���
		//	{
		//		hwnd2->SetFocus();
		//	}
		//} 
		//else//�����겻�ڰ�ť�ϣ�
		//{
		//	if (GetFocus()==hwnd2)//�����ť�н��㣬��ôȥ���㣻
		//	{
		//		GetDlgItem(IDC_BUTTON1)->SetFocus();//�����IDC_BUTTON1Ϊ����Ҫ��ת���Ŀؼ�ID��
		//	}
		//}
		//CDialog::OnTimer(nIDEvent);



	CDialog::OnMouseMove(nFlags, point);
}



IMPLEMENT_DYNAMIC(CCustomBmpBtn, CButton)
CCustomBmpBtn::CCustomBmpBtn()
	:m_bTrackingMouse(true)
{
	m_bOver = FALSE;
	
	m_bmpNormal.LoadBitmap(IDB_BITMAP_NORMAL);
	m_bmpHover.LoadBitmap(IDB_BITMAP_HUNG);
	m_bmpPress.LoadBitmap(IDB_BITMAP_CLICK);
	m_bmpFocus.LoadBitmap(IDB_BITMAP_FOCUS);
}
BEGIN_MESSAGE_MAP(CCustomBmpBtn, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

void CCustomBmpBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bTrackingMouse)
	{
		TRACKMOUSEEVENT cTrackMouse;
		cTrackMouse.cbSize=sizeof(cTrackMouse);
		cTrackMouse.hwndTrack=GetSafeHwnd();
		cTrackMouse.dwFlags=TME_LEAVE|TME_HOVER;
		cTrackMouse.dwHoverTime=10;
		if(::_TrackMouseEvent(&cTrackMouse))
		{
			m_bTrackingMouse=false;
		}
	}

	CButton::OnMouseMove(nFlags, point);
}

void CCustomBmpBtn::OnMouseLeave()
{
	m_bOver=FALSE;
	m_bTrackingMouse=true;
	InvalidateRect(NULL);

	CButton::OnMouseLeave();
}

void CCustomBmpBtn::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bOver=TRUE;	//���ͣ���ڰ�ť�Ϸ�
	m_bTrackingMouse=false;
	Invalidate(NULL);

	CButton::OnMouseHover(nFlags, point);
}

void CCustomBmpBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;

	CBitmap* pBmpShow=NULL;
	if(state & ODS_SELECTED)//ѡ��
	{
		pBmpShow=&m_bmpPress;
	}
	else if(state & ODS_FOCUS)//���н���
	{
		pBmpShow=&m_bmpFocus;
	}
	else if(m_bOver)//ͣ��
	{
		pBmpShow=&m_bmpHover;
	}
	else	//����״̬
	{
		pBmpShow=&m_bmpNormal;
	}

	BITMAP bmp;
	pBmpShow->GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(pBmpShow);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
		0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
}