
// SerializeView.cpp : CSerializeView 类的实现
//

#include "stdafx.h"
#include "Serialize.h"

#include "SerializeDoc.h"
#include "SerializeView.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerializeView

IMPLEMENT_DYNCREATE(CSerializeView, CView)

BEGIN_MESSAGE_MAP(CSerializeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSerializeView::OnFilePrintPreview)
	ON_COMMAND(ID_DOT, &CSerializeView::OnDot)
	ON_COMMAND(ID_LINE, &CSerializeView::OnLine)
	ON_COMMAND(ID_RECT, &CSerializeView::OnRect)
	ON_COMMAND(ID_ELLISPE, &CSerializeView::OnEllispe)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CSerializeView 构造/析构

CSerializeView::CSerializeView()
{
	// TODO: 在此处添加构造代码
	m_nDrawType=0;
	m_ptOrigin=0;

}

CSerializeView::~CSerializeView()
{
}

BOOL CSerializeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSerializeView 绘制

void CSerializeView::OnDraw(CDC* pDC)
{
	CSerializeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	int iCount;
	iCount=pDoc->m_obArray.GetSize();
	for(int i=0;i<iCount;i++)
	{
		//((CGraph*)m_obArray.GetAt(i))->Draw(pDC);
		((CGraph*)pDoc->m_obArray.GetAt(i))->Draw(pDC);
	}
}


// CSerializeView 打印


void CSerializeView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSerializeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSerializeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSerializeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSerializeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSerializeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSerializeView 诊断

#ifdef _DEBUG
void CSerializeView::AssertValid() const
{
	CView::AssertValid();
}

void CSerializeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSerializeDoc* CSerializeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSerializeDoc)));
	return (CSerializeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSerializeView 消息处理程序

//void CSerializeView::OnWrite()
//{
//	// TODO: 在此添加命令处理程序代码
//	CFile file(_T("1.txt"),CFile::modeCreate|CFile::modeWrite);
//	//构造存档对象
//	CArchive ar(&file,CArchive::store);
//	int i=4;
//	char ch='a';
//	float f=1.3f;
//	CString str("http://www.sunxin.org");
//	//保存数据
//	ar<<i<<ch<<f<<str;
//}

//void CSerializeView::OnRead()
//{
//	// TODO: 在此添加命令处理程序代码
//	CFile file(_T("1.txt"),CFile::modeRead);
//	CArchive ar(&file,CArchive::load);
//	int i;
//	char ch;
//	float f;
//	CString str;
//	CString strResult;
//	//读取数据
//	ar>>i>>ch>>f>>str;
//	strResult.Format(_T("%d,%c,%f,%s"),i,ch,f,str);
//	MessageBox(strResult);
//}

void CSerializeView::OnDot()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=1;
}

void CSerializeView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=2;
}

void CSerializeView::OnRect()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=3;
}

void CSerializeView::OnEllispe()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType=4;
}

void CSerializeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptOrigin=point;

	CView::OnLButtonDown(nFlags, point);
}

void CSerializeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);

	//switch(m_nDrawType)
	//{
	//case 1:
	//	dc.SetPixel(point,RGB(0,0,0));
	//	break;
	//case 2:
	//	dc.MoveTo(m_ptOrigin);
	//	dc.LineTo(point);
	//	break;;
	//case 3:
	//	dc.Rectangle(CRect(m_ptOrigin,point));
	//	break;
	//case 4:
	//	dc.Ellipse(CRect(m_ptOrigin,point));
	//	break;
	//}

	CGraph* pGraph=new CGraph(m_nDrawType,m_ptOrigin,point);
	//m_obArray.Add(pGraph);
	CSerializeDoc* pDoc=GetDocument();
	pDoc->m_obArray.Add(pGraph);

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}
