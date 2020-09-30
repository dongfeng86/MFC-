
// Menu3View.cpp : CMenu3View 类的实现
//

#include "stdafx.h"
#include "Menu3.h"

#include "Menu3Doc.h"
#include "Menu3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu3View

IMPLEMENT_DYNCREATE(CMenu3View, CView)

BEGIN_MESSAGE_MAP(CMenu3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMenu3View::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_COMMAND(IDM_PHONE1,OnPhone1)
	ON_COMMAND(IDM_PHONE2,OnPhone2)
	ON_COMMAND(IDM_PHONE3,OnPhone3)
	ON_COMMAND(IDM_PHONE4,OnPhone4)
END_MESSAGE_MAP()

// CMenu3View 构造/析构

CMenu3View::CMenu3View()
{
	// TODO: 在此处添加构造代码
	m_iIndex=-1;

}

CMenu3View::~CMenu3View()
{
}

BOOL CMenu3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMenu3View 绘制

void CMenu3View::OnDraw(CDC* /*pDC*/)
{
	CMenu3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMenu3View 打印


void CMenu3View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMenu3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMenu3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMenu3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMenu3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMenu3View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


void CMenu3View::OnPhone1()
{
	CClientDC dc(this);
	dc.TextOut(0,0,m_arsLines.GetAt(0));
}

void CMenu3View::OnPhone2()
{
	CClientDC dc(this);
	dc.TextOut(0,0,m_arsLines.GetAt(1));
}

void CMenu3View::OnPhone3()
{
	CClientDC dc(this);
	dc.TextOut(0,0,m_arsLines.GetAt(2));
}

void CMenu3View::OnPhone4()
{
	CClientDC dc(this);
	dc.TextOut(0,0,m_arsLines.GetAt(3));
}

// CMenu3View 诊断

#ifdef _DEBUG
void CMenu3View::AssertValid() const
{
	CView::AssertValid();
}

void CMenu3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMenu3Doc* CMenu3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMenu3Doc)));
	return (CMenu3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMenu3View 消息处理程序

void CMenu3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	if(0x0d==nChar)
	{
		if(0==++m_iIndex)
		{
			m_menu.CreatePopupMenu();
			GetParent()->GetMenu()->AppendMenu(MF_POPUP,(UINT)m_menu.m_hMenu,_T("PhoneBook"));
			GetParent()->DrawMenuBar();
		}
		m_menu.AppendMenu(MF_STRING,IDM_PHONE1+m_iIndex,m_strLine.Left(m_strLine.Find(' ')));
		m_arsLines.Add(m_strLine);
		m_strLine.Empty();
		Invalidate(TRUE);		//刷新客户区
	}
	else
	{
		m_strLine+=(TCHAR)nChar;
		dc.TextOut(0,0,m_strLine);
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}
