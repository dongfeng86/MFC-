
// TextView.cpp : CTextView 类的实现
//

#include "stdafx.h"
#include "Text.h"

#include "TextDoc.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextView

IMPLEMENT_DYNCREATE(CTextView, CView)

BEGIN_MESSAGE_MAP(CTextView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTextView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTextView 构造/析构

CTextView::CTextView()
: m_strLine(_T(""))
, m_ptOrigin(0)
, m_iWidth(0)
{
	// TODO: 在此处添加构造代码
}

CTextView::~CTextView()
{
}

BOOL CTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTextView 绘制

void CTextView::OnDraw(CDC* pDC)
{
	CTextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码

	CString str(_T("微信中兴"));
	pDC->TextOut(50,50,str);
	CSize sz=pDC->GetTextExtent(str);

	str.LoadString(IDS_WEIXIN);
	pDC->TextOut(50,100,str);

	//以下创建了一个路径层
	pDC->BeginPath();
	pDC->Rectangle(50,50,50+sz.cx,50+sz.cy);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_AND);

	for(int i=0;i<300;i+=10)
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(300,i);
		pDC->MoveTo(i,0);
		pDC->LineTo(i,300);
	}
}


// CTextView 打印

void CTextView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTextView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTextView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTextView 诊断

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextDoc* CTextView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextDoc)));
	return (CTextDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextView 消息处理程序

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//创建设备描述表
	CClientDC dc(this);
	//定义文本信息结构体变量
	TEXTMETRIC tm;
	//获得设备描述表中文本信息
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);
	ShowCaret();
	
	//显示一个位图提示符
	//m_bitmap.LoadBitmap(IDB_BITMAP1);
	//CreateCaret(&m_bitmap);
	//ShowCaret();

	SetTimer(1,100,NULL);

	return 0;
}

//响应该函数主要用于在view视图中显示字符
void CTextView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);

	CFont font;
	font.CreatePointFont(300,_T("华文行楷"),NULL);
	CFont *pOldFont = dc.SelectObject(&font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	if(0x0d==nChar)
	{
		m_strLine.Empty();
		m_ptOrigin.y+=tm.tmHeight;
	}
	else if(0x08==nChar)
	{
		COLORREF clr=dc.SetTextColor(dc.GetBkColor());
		dc.TextOut(m_ptOrigin.x,m_ptOrigin.y,m_strLine);
		m_strLine=m_strLine.Left(m_strLine.GetLength()-1);
		dc.SetTextColor(clr);
	}
	else
	{
		m_strLine+= (TCHAR)nChar;
	}

	dc.TextOut(m_ptOrigin.x,m_ptOrigin.y,m_strLine);

	CSize sz=dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.y=m_ptOrigin.y;
	pt.x=m_ptOrigin.x+sz.cx;
	SetCaretPos(pt);

	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTextView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCaretPos(point);
	m_strLine.Empty();
	m_ptOrigin=point;
	CView::OnLButtonDown(nFlags, point);
}

void CTextView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_iWidth+=5;
	CClientDC dc(this);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CRect rect;
	rect.left=0;
	rect.top=200;
	rect.right=m_iWidth;
	rect.bottom=rect.top+tm.tmHeight;

	dc.SetTextColor(RGB(255,0,0));
	CString str;
	str.LoadString(IDS_WEIXIN);
	dc.DrawText(str,rect,DT_RIGHT);

	CSize sz=dc.GetTextExtent(str);
	if(m_iWidth>sz.cx)
	{
		m_iWidth=0;
		//dc.SetTextColor(RGB(0,255,0));
		COLORREF clr=dc.SetTextColor(dc.GetBkColor());
		dc.TextOut(0,200,str);
	}

	CView::OnTimer(nIDEvent);
}