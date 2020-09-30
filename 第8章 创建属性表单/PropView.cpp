
// PropView.cpp : CPropView ���ʵ��
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

// CPropView ����/����

CPropView::CPropView()
:m_iOccupation(-1)
,m_strWorkerAddr(_T(""))
,m_strSalary(_T(""))
{
	// TODO: �ڴ˴���ӹ������
	memset(m_bLike,0,sizeof(m_bLike));

}

CPropView::~CPropView()
{
}

BOOL CPropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPropView ����

void CPropView::OnDraw(CDC* pDC)
{
	CPropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CFont font;
	font.CreatePointFont(300,_T("�����п�"));
	CFont * pPreFont;
	pPreFont=pDC->SelectObject(&font);
	
	CString strTemp;
	strTemp=_T("���ְҵ");

	switch(m_iOccupation)
	{
	case 0:
		strTemp+=_T("����Ա");
		break;
	case 1:
		strTemp+=_T("ϵͳ����ʦ");
		break;
	case 2:
		strTemp+=_T("��Ŀ����");
		break;
	default:
		break;
	}
	
	pDC->TextOut(0,0,strTemp);

	strTemp=_T("��Ĺ����ص�:");
	strTemp+=m_strWorkerAddr;

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	pDC->TextOut(0,tm.tmHeight,strTemp);
	
	strTemp=_T("�����Ȥ����:");
	if(m_bLike[0])
	{
		strTemp+=_T("����");
	}
	if(m_bLike[1])
	{
		strTemp+=_T("����");
	}
	if(m_bLike[2])
	{
		strTemp+=_T("����");
	}
	if(m_bLike[3])
	{
		strTemp+=_T("��Ӿ");
	}
	
	pDC->TextOut(0,tm.tmHeight*2,strTemp);

	strTemp=_T("���н��ˮƽ:");
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


// CPropView ���

#ifdef _DEBUG
void CPropView::AssertValid() const
{
	CView::AssertValid();
}

void CPropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropDoc* CPropView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropDoc)));
	return (CPropDoc*)m_pDocument;
}
#endif //_DEBUG


// CPropView ��Ϣ�������

void CPropView::OnPropsheet()
{
	// TODO: �ڴ���������������
	//�������Ա�
	CPropSheet propSheet(_T("���Ա�"));
	propSheet.DoModal();

	//������
	//CPropSheet propSheet(_T("ά�����Ա�����"));
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
