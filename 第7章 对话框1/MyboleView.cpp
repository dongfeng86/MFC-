
// MyboleView.cpp : CMyboleView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyboleView::OnFilePrintPreview)
	ON_COMMAND(IDM_DLG, &CMyboleView::OnDlg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMyboleView ����/����

CMyboleView::CMyboleView()
{
	// TODO: �ڴ˴���ӹ������

}

CMyboleView::~CMyboleView()
{
}

BOOL CMyboleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyboleView ����

void CMyboleView::OnDraw(CDC* /*pDC*/)
{
	CMyboleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMyboleView ��ӡ


void CMyboleView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMyboleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyboleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyboleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMyboleView ���

#ifdef _DEBUG
void CMyboleView::AssertValid() const
{
	CView::AssertValid();
}

void CMyboleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyboleDoc* CMyboleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyboleDoc)));
	return (CMyboleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyboleView ��Ϣ�������

void CMyboleView::OnDlg()
{
	// TODO: �ڴ���������������
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

	// TODO: �ڴ˴������Ϣ����������
}
