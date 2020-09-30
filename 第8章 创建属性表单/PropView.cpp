
// PropView.cpp : CPropView 类的实现
//

#include "stdafx.h"
#include "Prop.h"

#include "PropDoc.h"
#include "PropView.h"
#include "CPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropView

IMPLEMENT_DYNCREATE(CPropView, CView)

BEGIN_MESSAGE_MAP(CPropView, CView)
	ON_COMMAND(ID_PROPSHEET, &CPropView::OnPropsheet)
END_MESSAGE_MAP()

// CPropView 构造/析构

CPropView::CPropView()
:m_iOccupation(-1)
,m_strWorkerAddr(_T(""))
,m_strSalary(_T(""))
{
	// TODO: 在此处添加构造代码
	memset(m_bLike,0,sizeof(m_bLike));

}

CPropView::~CPropView()
{
}

BOOL CPropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPropView 绘制

void CPropView::OnDraw(CDC* pDC)
{
	CPropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CFont font;
	font.CreatePointFont(300,_T("华文行楷"));
	CFont * pPreFont;
	pPreFont=pDC->SelectObject(&font);
	
	CString strTemp;
	strTemp=_T("你的职业");

	switch(m_iOccupation)
	{
	case 0:
		strTemp+=_T("程序员");
		break;
	case 1:
		strTemp+=_T("系统工程师");
		break;
	case 2:
		strTemp+=_T("项目经理");
		break;
	default:
		break;
	}
	
	pDC->TextOut(0,0,strTemp);

	strTemp=_T("你的工作地点:");
	strTemp+=m_strWorkerAddr;

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	pDC->TextOut(0,tm.tmHeight,strTemp);
	
	strTemp=_T("你的兴趣爱好:");
	if(m_bLike[0])
	{
		strTemp+=_T("足球");
	}
	if(m_bLike[1])
	{
		strTemp+=_T("篮球");
	}
	if(m_bLike[2])
	{
		strTemp+=_T("排球");
	}
	if(m_bLike[3])
	{
		strTemp+=_T("游泳");
	}
	
	pDC->TextOut(0,tm.tmHeight*2,strTemp);

	strTemp=_T("你的薪资水平:");
	strTemp+=m_strSalary;
	pDC->TextOut(0,tm.tmHeight*3,strTemp);

	pDC->SelectObject(pPreFont);


}

void CPropView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPropView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CPropView 诊断

#ifdef _DEBUG
void CPropView::AssertValid() const
{
	CView::AssertValid();
}

void CPropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropDoc* CPropView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropDoc)));
	return (CPropDoc*)m_pDocument;
}
#endif //_DEBUG


// CPropView 消息处理程序

void CPropView::OnPropsheet()
{
	// TODO: 在此添加命令处理程序代码
	//创建属性表单
	CPropSheet propSheet(_T("属性表单"));
	propSheet.DoModal();

	//创建向导
	//CPropSheet propSheet(_T("维新属性表单程序"));
	//propSheet.SetWizardMode();
	//if(ID_WIZFINISH == propSheet.DoModal())
	//{
	//	m_iOccupation=propSheet.m_prop1.m_occupation;
	//	m_strWorkerAddr=propSheet.m_prop1.m_strAddr;
	//	m_bLike[0]=propSheet.m_prop2.m_bFootBall;
	//	m_bLike[1]=propSheet.m_prop2.m_bBasketBall;
	//	m_bLike[2]=propSheet.m_prop2.m_bVolBall;
	//	m_bLike[3]=propSheet.m_prop2.m_bSwim;
	//	m_strSalary=propSheet.m_prop3.m_strSalary;
	//	Invalidate();
	//}
}
