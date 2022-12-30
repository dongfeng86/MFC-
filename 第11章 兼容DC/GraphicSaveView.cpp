
// GraphicSaveView.cpp : CGraphicSaveView 类的实现
//

#include "stdafx.h"
#include "GraphicSave.h"

#include "GraphicSaveDoc.h"
#include "GraphicSaveView.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicSaveView

IMPLEMENT_DYNCREATE(CGraphicSaveView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicSaveView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicSaveView::OnFilePrintPreview)
	ON_COMMAND(ID_DOT, &CGraphicSaveView::OnDot)
	ON_COMMAND(ID_LINE, &CGraphicSaveView::OnLine)
	ON_COMMAND(ID_RECT, &CGraphicSaveView::OnRect)
	ON_COMMAND(ID_ELLISPE, &CGraphicSaveView::OnEllispe)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CGraphicSaveView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CGraphicSaveView::OnFileSave)
END_MESSAGE_MAP()

// CGraphicSaveView 构造/析构

CGraphicSaveView::CGraphicSaveView()
{
	// TODO: 在此处添加构造代码
	m_nDrawType=0;
	m_ptOrigin=0;
}

CGraphicSaveView::~CGraphicSaveView()
{
	for(INT_PTR i=0;i<m_arpObjects.GetSize();i++)
	{
		delete (CGraph*)(m_arpObjects.GetAt(i));
	}
	m_arpObjects.RemoveAll();
}

BOOL CGraphicSaveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicSaveView 绘制

void CGraphicSaveView::OnDraw(CDC* pDC)
{
	CGraphicSaveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),
		&m_dcCompatible,0,0,SRCCOPY);
}


// CGraphicSaveView 打印


void CGraphicSaveView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CGraphicSaveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicSaveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicSaveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGraphicSaveView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicSaveView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGraphicSaveView 诊断

#ifdef _DEBUG
void CGraphicSaveView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicSaveView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicSaveDoc* CGraphicSaveView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicSaveDoc)));
	return (CGraphicSaveDoc*)m_pDocument;
}
#endif //_DEBUG



void CGraphicSaveView::OnDot()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=1;
}

void CGraphicSaveView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=2;
}

void CGraphicSaveView::OnRect()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=3;
}

void CGraphicSaveView::OnEllispe()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=4;
}

void CGraphicSaveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptOrigin=point;
	
	CScrollView::OnLButtonDown(nFlags, point);
}

//void CGraphicSaveView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CClientDC dc(this);	
//	//CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
//	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
//
//	//if(!m_dcCompatible.m_hDC)
//	//{
//	//	m_dcCompatible.CreateCompatibleDC(&dc);
//	//	CRect rect;
//	//	GetClientRect(&rect);
//
//	//	CBitmap bitmap;
//	//	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
//
//	//	CBitmap* pOldBmp=NULL;
//	//	pOldBmp=m_dcCompatible.SelectObject(&bitmap);
//	//	if(pOldBmp)
//	//		pOldBmp->DeleteObject();
//
//	//	CBrush* pOldBrush=NULL;
//	//	m_dcCompatible.BitBlt(0,0,rect.Width(),rect.Height(),
//	//		&dc,0,0,SRCCOPY);
//	//	pOldBrush=m_dcCompatible.SelectObject(pBrush);
//	//	if(pOldBrush)
//	//		pOldBrush->DeleteObject();
//
//	//	m_penSel.CreatePen(PS_COSMETIC, 1, RGB(255,0,0));
//	//	CPen* pOldPen=NULL;
//	//	pOldPen=m_dcCompatible.SelectObject(&m_penSel);
//	//	if(pOldPen)
//	//		pOldPen->DeleteObject();
//	//	
//	//}
//
//	if(!m_dcCompatible.m_hDC)
//	{
//		m_dcCompatible.CreateCompatibleDC(&dc);	
//	}
//
//	CRect rect;
//	GetClientRect(&rect);
//
//	CBitmap bitmap;
//	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
//
//	CBitmap* pOldBmp=NULL;
//	pOldBmp=m_dcCompatible.SelectObject(&bitmap);
//	if(pOldBmp)
//		pOldBmp->DeleteObject();
//
//	CBrush* pOldBrush=NULL;
//	m_dcCompatible.BitBlt(0,0,rect.Width(),rect.Height(),
//		&dc,0,0,SRCCOPY);		//调用该函数将原始设备描述表的颜色表及像素数据库复制到兼容设备描述表
//	pOldBrush=m_dcCompatible.SelectObject(pBrush);
//
//	CPen pen;
//	pen.CreatePen(PS_COSMETIC, 1, RGB(255,0,0));
//	CPen* pOldPen=NULL;
//	pOldPen=m_dcCompatible.SelectObject(&pen);
//
//	switch(m_nDrawType)
//	{
//	case 1:
//		m_dcCompatible.SetPixel(point,RGB(0,0,0));
//		break;
//	case 2:
//		m_dcCompatible.MoveTo(m_ptOrigin);
//		m_dcCompatible.LineTo(point);
//		break;;
//	case 3:
//		m_dcCompatible.Rectangle(CRect(m_ptOrigin,point));
//		break;
//	case 4:
//		m_dcCompatible.Ellipse(CRect(m_ptOrigin,point));
//		break;
//	}
//	
//	//m_dcCompatible.SelectObject(pOldBmp);
//	m_dcCompatible.SelectObject(pOldBrush);
//	m_dcCompatible.SelectObject(pOldPen);
//
//	CScrollView::OnLButtonUp(nFlags, point);
//	Invalidate();
//}

void GetLargestDisplayMode(int * pcxBitmap, int * pcyBitmap)
{
	DEVMODE devmode;
	int     iModeNum = 0;

	*pcxBitmap = *pcyBitmap = 0;

	ZeroMemory(&devmode, sizeof(DEVMODE));
	devmode.dmSize = sizeof(DEVMODE);

	while (EnumDisplaySettings(NULL, iModeNum++, &devmode))
	{
		*pcxBitmap = max(*pcxBitmap, (int)devmode.dmPelsWidth);
		*pcyBitmap = max(*pcyBitmap, (int)devmode.dmPelsHeight);
	}
}

void CGraphicSaveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	if (!m_dcCompatible.m_hDC)
	{
		m_dcCompatible.CreateCompatibleDC(&dc);
	}

	if (!m_bmpMemory.m_hObject)
	{
		int cxBitmap, cyBitmap;
		GetLargestDisplayMode(&cxBitmap, &cyBitmap);
		m_bmpMemory.CreateCompatibleBitmap(&dc, cxBitmap, cyBitmap);
		CBitmap* pOldBmp = NULL;
		pOldBmp = m_dcCompatible.SelectObject(&m_bmpMemory);
		if (pOldBmp)
			pOldBmp->DeleteObject();
		m_dcCompatible.PatBlt(0, 0, cxBitmap, cyBitmap, WHITENESS);
	}

	CBrush* pOldBrush = NULL;
	pOldBrush = m_dcCompatible.SelectObject(pBrush);

	CPen pen;
	pen.CreatePen(PS_COSMETIC, 1, RGB(255, 0, 0));
	CPen* pOldPen = NULL;
	pOldPen = m_dcCompatible.SelectObject(&pen);

	switch (m_nDrawType)
	{
	case 1:
		m_dcCompatible.SetPixel(point, RGB(0, 0, 0));
		break;
	case 2:
		m_dcCompatible.MoveTo(m_ptOrigin);
		m_dcCompatible.LineTo(point);
		break;;
	case 3:
		m_dcCompatible.Rectangle(CRect(m_ptOrigin, point));
		break;
	case 4:
		m_dcCompatible.Ellipse(CRect(m_ptOrigin, point));
		break;
	}

	//m_dcCompatible.SelectObject(pOldBmp);
	m_dcCompatible.SelectObject(pOldBrush);
	m_dcCompatible.SelectObject(pOldPen);

	CScrollView::OnLButtonUp(nFlags, point);
	Invalidate();
}

void CGraphicSaveView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CScrollView::OnPaint()
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CGraphicSaveView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	SetScrollSizes(MM_TEXT,CSize(800,600));
}

void CGraphicSaveView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	HMETAFILE hMetaFile;
	hMetaFile=GetMetaFile(_T("meta.wmf"));
	m_dcMetaFile.PlayMetaFile(hMetaFile);
	DeleteMetaFile(hMetaFile);
	Invalidate();
}

void CGraphicSaveView::OnFileSave()
{
	HMETAFILE hMetaFile;
	hMetaFile=m_dcMetaFile.Close();
	CopyMetaFile(hMetaFile,_T("meta.wmf"));
	m_dcMetaFile.Create();
	DeleteMetaFile(hMetaFile);
}
