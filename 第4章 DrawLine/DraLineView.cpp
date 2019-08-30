
// DraLineView.cpp : CDraLineView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDraLineView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDraLineView ����/����

CDraLineView::CDraLineView()
:m_ptOrigin(0,0)
,m_bDraw(FALSE)
{
	// TODO: �ڴ˴���ӹ������
}

CDraLineView::~CDraLineView()
{
}

BOOL CDraLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDraLineView ����

void CDraLineView::OnDraw(CDC* /*pDC*/)
{
	CDraLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDraLineView ��ӡ


void CDraLineView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CDraLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDraLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDraLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CDraLineView ���

#ifdef _DEBUG
void CDraLineView::AssertValid() const
{
	CView::AssertValid();
}

void CDraLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDraLineDoc* CDraLineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDraLineDoc)));
	return (CDraLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CDraLineView ��Ϣ�������

void CDraLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	m_ptOrigin=point;
	m_bDraw=TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CDraLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//����ȫ�ֺ�������ֱ��
	//HDC hdc;
	//hdc=::GetDC(m_hWnd);           //CView��CWnd������������ˣ��̳���CWnd�ĳ�Ա
	//::MoveToEx(hdc,m_ptOrigin.x,m_ptOrigin.y,NULL);
	//::LineTo(hdc,point.x,point.y);
	//::ReleaseDC(m_hWnd,hdc);
	//

	//����CDC����л�ͼ
	/*
	CDC *pDc=GetDC();
	pDc->MoveTo(m_ptFir);
	pDc->LineTo(point);
	ReleaseDC(pDc);
	*/

	//����CClientDC��ʵ�ֻ��߹���
	/*
	CClientDC dc(GetParent());
	dc.MoveTo(m_ptFir);
	dc.LineTo(point);
	*/

	//����CWindowDC����л�ͼ
	/*
	CWindowDC dc(GetDesktopWindow());
	dc.MoveTo(m_ptFir);
	dc.LineTo(point);
	*/
	
	//��ӻ��ʵ��豸��������
	
	//CPen pen(PS_SOLID,5,RGB(255,0,0));
	//CClientDC dc(this);
	//CPen * pOldPen=dc.SelectObject(&pen);
	//dc.MoveTo(m_ptFir);
	//dc.LineTo(point);
	//dc.SelectObject(pOldPen);
	

	//ʹ�û�ˢ
	
	//CBrush brush(RGB(255,0,0));
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptFir,point),&brush);
	

	////ʹ��λͼ��ˢ
	//CBitmap bitmap;
	////����λͼ��Դ
	//bitmap.LoadBitmap(IDB_BITMAP1);
	////����λͼ��ˢ
	//CBrush brush(&bitmap);
	////����������豸������
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptOrigin,point),&brush);

	m_bDraw=FALSE;           //������������ʱ�ж�����Ƿ���

	CView::OnLButtonUp(nFlags, point);
}

//�ô��ڹ��̺���ģ������ƶ���������
void CDraLineView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	//������ɫ�Ļ���
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	//�ѻ��ʷŽ��豸��������
	CPen * pOldPen=dc.SelectObject(&pen);
	if(TRUE==m_bDraw)
	{
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		//�޸��߶ε���㣬��Ȼ�ͳ�������
		m_ptOrigin=point;
	}
	//�ָ��豸������
	dc.SelectObject(pOldPen);

	CView::OnMouseMove(nFlags, point);
}
