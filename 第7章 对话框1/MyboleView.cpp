
// MyboleView.cpp : CMyboleView 类的实现
//

#include "stdafx.h"
#include "Mybole.h"
#include "CTestDlg.h"

#include "MyboleDoc.h"
#include "MyboleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyboleView

IMPLEMENT_DYNCREATE(CMyboleView, CView)

BEGIN_MESSAGE_MAP(CMyboleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyboleView::OnFilePrintPreview)
	ON_COMMAND(IDM_DLG, &CMyboleView::OnDlg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMyboleView 构造/析构

CMyboleView::CMyboleView()
{
	// TODO: 在此处添加构造代码

}

CMyboleView::~CMyboleView()
{
}

BOOL CMyboleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyboleView 绘制

void CMyboleView::OnDraw(CDC* /*pDC*/)
{
	CMyboleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyboleView 打印


void CMyboleView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMyboleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyboleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyboleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyboleView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyboleView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMyboleView 诊断

#ifdef _DEBUG
void CMyboleView::AssertValid() const
{
	CView::AssertValid();
}

void CMyboleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyboleDoc* CMyboleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyboleDoc)));
	return (CMyboleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyboleView 消息处理程序

void CMyboleView::OnDlg()
{
	// TODO: 在此添加命令处理程序代码
	CTestDlg dlg;
	dlg.DoModal();

	//CTestDlg* pDlg=new CTestDlg();
	//pDlg->Create(IDD_DLG_MAIN,this);
	//pDlg->ShowWindow(SW_SHOWNORMAL);

	//CTestDlg dlg;
	//dlg.Create(IDD_DLG_MAIN,this);
	//dlg.ShowWindow(SW_SHOWNORMAL);

	//CTestDlg * pDlg=new CTestDlg();
	//pDlg->Create(IDD_DLG_MAIN,this);
	//pDlg->ShowWindow(SW_SHOWNORMAL);
}


void CMyboleView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
