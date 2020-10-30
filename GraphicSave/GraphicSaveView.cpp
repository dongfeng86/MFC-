
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
	CBrush* pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	pDC->SelectObject(pBrush);

	CGraph* pGraph=NULL;
	for(int i=0;i<m_arpObjects.GetSize();i++)
	{
		pGraph=(CGraph*)m_arpObjects.GetAt(i);
		switch((pGraph->m_nDrawType))
		{
		case 1:
			pDC->SetPixel(pGraph->m_ptEnd,RGB(0,0,0));
			break;
		case 2:
			pDC->MoveTo(pGraph->m_ptOrigin);
			pDC->LineTo(pGraph->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(pGraph->m_ptOrigin,pGraph->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(pGraph->m_ptOrigin,pGraph->m_ptEnd));
			break;
		}
	}
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

void CGraphicSaveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);

	switch(m_nDrawType)
	{
	case 1:
		dc.SetPixel(point,RGB(0,0,0));
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin,point));
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin,point));
		break;
	}

	OnPrepareDC(&dc);
	dc.DPtoLP(&m_ptOrigin);
	dc.DPtoLP(&point);

	CGraph* pGraph=new CGraph(m_nDrawType,m_ptOrigin,point);
	m_arpObjects.Add(pGraph);
	
	CScrollView::OnLButtonUp(nFlags, point);
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
