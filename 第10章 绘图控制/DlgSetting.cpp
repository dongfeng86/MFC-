// DlgSetting.cpp : 实现文件
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
	m_font.CreatePointFont(200,_T("华文行楷"));
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


// CDlgSetting 消息处理程序

void CDlgSetting::OnEnChangeEdtLinewidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
}

void CDlgSetting::OnBnClickedRad1()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}

void CDlgSetting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
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

//如何更改控件的背景和颜色（注意，这种方法不能改变按钮控件的背景和颜色）
HBRUSH CDlgSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if(pWnd->GetDlgCtrlID()==IDC_LINESTYLE)
	{
		//经试验，这两句无效
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID()==IDC_EDT_LINEWIDTH)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(0,255,0)); //两种方式均可以
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

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//经验证，这种方法有问题，窗口拉伸后背景图片失真
//BOOL CDlgSetting::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

	//以下代码显示不正常，按钮里面的图片仅仅显示一部分

	//CBitmap bmp;
	//bmp.LoadBitmap(IDB_BITMAP3);
	//HBITMAP hBmp;
	//hBmp=(HBITMAP)bmp.Detach();
	//m_wndTestBad.LoadBitmaps(IDB_BITMAP_NORMAL,IDB_BITMAP_CLICK,IDB_BITMAP_HUNG);
	//m_wndTestBad.SizeToContent(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSetting::OnMouseMove(UINT nFlags, CPoint point)
{
	//SetFocus();


	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//POINT pt;
	//GetCursorPos(&pt);
	//CWnd* hWnd=NULL;
	//ScreenToClient(&pt);
	//hWnd=ChildWindowFromPoint(pt);
	//CWnd* pWnd2=GetDlgItem(IDC_BTN_NEW);
	//if(hWnd==pWnd2)
	//{
	//	MessageBox(_T("捕获到了鼠标位置\n"));
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
	//	MessageBox(_T("捕获到了鼠标位置\n"));
	//}

	//CRect rect;
	//GetClientRect(&rect);         //图片的矩形
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
		//hwnd = WindowFromPoint(p);//检索窗口中包含制定的点；点必须指定屏幕坐标在屏幕上的一个点。
		//CWnd *hwnd2=GetDlgItem(IDC_BUTTON2);
		//if (hwnd2==hwnd)//如果鼠标在按钮上
		//{
		//	if (GetFocus()!=hwnd2)//如果按钮无焦点，那么设置焦点
		//	{
		//		hwnd2->SetFocus();
		//	}
		//} 
		//else//如果鼠标不在按钮上；
		//{
		//	if (GetFocus()==hwnd2)//如果按钮有焦点，那么去焦点；
		//	{
		//		GetDlgItem(IDC_BUTTON1)->SetFocus();//这里的IDC_BUTTON1为你想要跳转到的控件ID号
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
	m_bOver=TRUE;	//鼠标停留在按钮上方
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
	if(state & ODS_SELECTED)//选中
	{
		pBmpShow=&m_bmpPress;
	}
	else if(state & ODS_FOCUS)//具有焦点
	{
		pBmpShow=&m_bmpFocus;
	}
	else if(m_bOver)//停留
	{
		pBmpShow=&m_bmpHover;
	}
	else	//正常状态
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