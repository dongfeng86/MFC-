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
}

BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	ON_EN_CHANGE(IDC_EDT_LINEWIDTH, &CDlgSetting::OnEnChangeEdtLinewidth)
	ON_BN_CLICKED(IDC_RAD_1, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_2, &CDlgSetting::OnBnClickedRad1)
	ON_BN_CLICKED(IDC_RAD_3, &CDlgSetting::OnBnClickedRad1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
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
