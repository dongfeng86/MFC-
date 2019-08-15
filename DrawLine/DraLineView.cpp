
// DraLineView.cpp : CDraLineView 类的实现
//

#include "stdafx.h"
#include "DraLine.h"

#include "DraLineDoc.h"
#include "DraLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraLineView

IMPLEMENT_DYNCREATE(CDraLineView, CView)

BEGIN_MESSAGE_MAP(CDraLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDraLineView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CDraLineView 构造/析构

CDraLineView::CDraLineView()
:m_ptFir(0,0)
{
	// TODO: 在此处添加构造代码
}

CDraLineView::~CDraLineView()
{
}

BOOL CDraLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDraLineView 绘制

void CDraLineView::OnDraw(CDC* /*pDC*/)
{
	CDraLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDraLineView 打印


void CDraLineView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CDraLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDraLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDraLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDraLineView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDraLineView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CDraLineView 诊断

#ifdef _DEBUG
void CDraLineView::AssertValid() const
{
	CView::AssertValid();
}

void CDraLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDraLineDoc* CDraLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDraLineDoc)));
	return (CDraLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CDraLineView 消息处理程序

void CDraLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	m_ptFir=point;
	//MessageBox(_T("click in the vieww"));
	CView::OnLButtonDown(nFlags, point);
}

void CDraLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//HDC hdc;
	//hdc=::GetDC(m_hWnd);           //CView从CWnd派生而来，因此，继承了CWnd的成员
	//MoveToEx(hdc,m_ptFir.x,m_ptFir.y,NULL);
	//LineTo(hdc,point.x,point.y);
	//::ReleaseDC(m_hWnd,hdc);
	CDC *pDc=GetDC();
	pDc->MoveTo(m_ptFir);
	pDc->LineTo(point);
	ReleaseDC(pDc);

	CView::OnLButtonUp(nFlags, point);
}
