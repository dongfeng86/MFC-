
// GraphicView.cpp : CGraphicView ���ʵ��
//

#include "stdafx.h"
#include "Graphic.h"

#include "GraphicDoc.h"
#include "GraphicView.h"
#include "TestBtn.h"

#include "DlgSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

BEGIN_MESSAGE_MAP(CGraphicView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicView::OnFilePrintPreview)
	ON_COMMAND(ID_POINT, &CGraphicView::OnPoint)
	ON_COMMAND(ID_LINE, &CGraphicView::OnLine)
	ON_COMMAND(ID_RECTANGE, &CGraphicView::OnRectange)
	ON_COMMAND(ID_ELLIPSE, &CGraphicView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SETTING, &CGraphicView::OnSetting)
	ON_COMMAND(ID_COLOR, &CGraphicView::OnColor)
	ON_COMMAND(ID_FONT, &CGraphicView::OnFont)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGraphicView ����/����

CGraphicView::CGraphicView()
{
	// TODO: �ڴ˴���ӹ������
	m_nDrawType=0;
	m_ptOrigin=0;
	m_nLineWidth=0;
	m_clr=RGB(255,0,0);
	m_strFontName=_T("");
}

CGraphicView::~CGraphicView()
{
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGraphicView ����

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CFont* pOldFont=pDC->SelectObject(&m_font);
	pDC->TextOut(0,0,m_strFontName);
	pDC->SelectObject(pOldFont);
}


// CGraphicView ��ӡ


void CGraphicView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGraphicView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicDoc* CGraphicView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicDoc)));
	return (CGraphicDoc*)m_pDocument;
}
#endif //_DEBUG


void CGraphicView::OnPoint()
{
	// TODO: �ڴ���������������
	m_nDrawType=1;
}

void CGraphicView::OnLine()
{
	// TODO: �ڴ���������������
	m_nDrawType=2;
}

void CGraphicView::OnRectange()
{
	// TODO: �ڴ���������������
	m_nDrawType=3;
}

void CGraphicView::OnEllipse()
{
	// TODO: �ڴ���������������
	m_nDrawType=4;
}

void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptOrigin=point;

	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);
	dc.SelectObject(&pen);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	switch(m_nDrawType)
	{
	case 1:
		dc.SetPixel(point,RGB(m_clr,0,0));
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin,point));
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin,point));
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CGraphicView::OnSetting()
{
	// TODO: �ڴ���������������
	CDlgSetting dlg;
	dlg.m_clr=m_clr;
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;
	}
}

//����Ϊ��ɫ�Ի���Ĳ�����ʽ
void CGraphicView::OnColor()
{
	// TODO: �ڴ���������������
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult=m_clr;
	if(IDOK==dlg.DoModal())
	{
		m_clr=dlg.m_cc.rgbResult;
	}
}

//����Ϊ����Ի���Ĳ�����ʽ
void CGraphicView::OnFont()
{
	CFontDialog dlg;
	if(IDOK==dlg.DoModal())
	{
		if(m_font.m_hObject)
			m_font.DeleteObject();

		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName=dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();
	}
}

void CGraphicView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()

	CView::OnPaint();
}

//����֤����view������ӱ���ͼƬ�Ĵ��룬����������ʾ����dialog������ӱ���ͼƬ���޷�������ʾ
BOOL CGraphicView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(&bitmap);

	CRect rect;
	GetClientRect(&rect);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
		0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);

	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
