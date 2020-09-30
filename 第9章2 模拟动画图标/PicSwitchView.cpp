
// PicSwitchView.cpp : CPicSwitchView ���ʵ��
//

#include "stdafx.h"
#include "PicSwitch.h"

#include "PicSwitchDoc.h"
#include "PicSwitchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicSwitchView

IMPLEMENT_DYNCREATE(CPicSwitchView, CView)

BEGIN_MESSAGE_MAP(CPicSwitchView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPicSwitchView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPicSwitchView ����/����

CPicSwitchView::CPicSwitchView()
{
	// TODO: �ڴ˴���ӹ������

}

CPicSwitchView::~CPicSwitchView()
{
}

BOOL CPicSwitchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPicSwitchView ����

void CPicSwitchView::OnDraw(CDC* /*pDC*/)
{
	CPicSwitchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPicSwitchView ��ӡ


void CPicSwitchView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CPicSwitchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPicSwitchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPicSwitchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPicSwitchView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPicSwitchView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CPicSwitchView ���

#ifdef _DEBUG
void CPicSwitchView::AssertValid() const
{
	CView::AssertValid();
}

void CPicSwitchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicSwitchDoc* CPicSwitchView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicSwitchDoc)));
	return (CPicSwitchDoc*)m_pDocument;
}
#endif //_DEBUG


// CPicSwitchView ��Ϣ�������
