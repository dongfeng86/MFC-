
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
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDraLineView 构造/析构

CDraLineView::CDraLineView()
:m_ptOrigin(0,0)
,m_bDraw(FALSE)
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
	
	m_ptOrigin=point;
	m_bDraw=TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CDraLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//利用全局函数绘制直线
	//HDC hdc;
	//hdc=::GetDC(m_hWnd);           //CView从CWnd派生而来，因此，继承了CWnd的成员
	//::MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,NULL);
	//::LineTo(hdc,point.x,point.y);
	//::ReleaseDC(m_hWnd,hdc);
	//

	//利用CDC类进行绘图
	/*
	CDC *pDc=GetDC();
	pDc->MoveTo(m_ptFir);
	pDc->LineTo(point);
	ReleaseDC(pDc);
	*/

	//利用CClientDC类实现画线功能
	/*
	CClientDC dc(GetParent());
	dc.MoveTo(m_ptFir);
	dc.LineTo(point);
	*/

	//利用CWindowDC类进行绘图
	/*
	CWindowDC dc(GetDesktopWindow());
	dc.MoveTo(m_ptFir);
	dc.LineTo(point);
	*/
	
	//添加画笔到设备上下文中
	
	//CPen pen(PS_SOLID,5,RGB(255,0,0));
	//CClientDC dc(this);
	//CPen * pOldPen=dc.SelectObject(&pen);
	//dc.MoveTo(m_ptFir);
	//dc.LineTo(point);
	//dc.SelectObject(pOldPen);
	

	//使用画刷
	
	//CBrush brush(RGB(255,0,0));
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptFir,point),&brush);
	

	////使用位图画刷
	//CBitmap bitmap;
	////加载位图资源
	//bitmap.LoadBitmap(IDB_BITMAP1);
	////创建位图画刷
	//CBrush brush(&bitmap);
	////创建并获得设备描述表
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptOrigin,point),&brush);

	m_bDraw=FALSE;           //用于连续画线时判断鼠标是否弹起

	CView::OnLButtonUp(nFlags, point);
}

//该窗口过程函数模拟鼠标移动连续画线
void CDraLineView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	//创建红色的画笔
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	//把画笔放进设备上下文中
	CPen * pOldPen=dc.SelectObject(&pen);
	if(TRUE==m_bDraw)
	{
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		//修改线段的起点，不然就成扇形了
		m_ptOrigin=point;
	}
	//恢复设备描述表
	dc.SelectObject(pOldPen);

	CView::OnMouseMove(nFlags, point);
}
