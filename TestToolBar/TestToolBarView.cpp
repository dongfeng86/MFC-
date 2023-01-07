
// TestToolBarView.cpp: CTestToolBarView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestToolBar.h"
#endif

#include "TestToolBarDoc.h"
#include "TestToolBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestToolBarView

IMPLEMENT_DYNCREATE(CTestToolBarView, CView)

BEGIN_MESSAGE_MAP(CTestToolBarView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestToolBarView 构造/析构

CTestToolBarView::CTestToolBarView() noexcept
{
	// TODO: 在此处添加构造代码

}

CTestToolBarView::~CTestToolBarView()
{
}

BOOL CTestToolBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestToolBarView 绘图

void CTestToolBarView::OnDraw(CDC* /*pDC*/)
{
	CTestToolBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTestToolBarView 打印

BOOL CTestToolBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestToolBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestToolBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestToolBarView 诊断

#ifdef _DEBUG
void CTestToolBarView::AssertValid() const
{
	CView::AssertValid();
}

void CTestToolBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestToolBarDoc* CTestToolBarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestToolBarDoc)));
	return (CTestToolBarDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestToolBarView 消息处理程序
