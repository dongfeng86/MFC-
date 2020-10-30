
// GraphicSaveView.cpp : CGraphicSaveView ���ʵ��
//

#include "stdafx.h"
#include "GraphicSave.h"

#include "GraphicSaveDoc.h"
#include "GraphicSaveView.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicSaveView

IMPLEMENT_DYNCREATE(CGraphicSaveView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicSaveView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicSaveView::OnFilePrintPreview)
	ON_COMMAND(ID_DOT, &CGraphicSaveView::OnDot)
	ON_COMMAND(ID_LINE, &CGraphicSaveView::OnLine)
	ON_COMMAND(ID_RECT, &CGraphicSaveView::OnRect)
	ON_COMMAND(ID_ELLISPE, &CGraphicSaveView::OnEllispe)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CGraphicSaveView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CGraphicSaveView::OnFileSave)
END_MESSAGE_MAP()

// CGraphicSaveView ����/����

CGraphicSaveView::CGraphicSaveView()
{
	// TODO: �ڴ˴���ӹ������
	m_nDrawType=0;
	m_ptOrigin=0;

}

CGraphicSaveView::~CGraphicSaveView()
{
	for(INT_PTR i=0;i<m_arpObjects.GetSize();i++)
	{
		delete (CGraph*)(m_arpObjects.GetAt(i));
	}
	m_arpObjects.RemoveAll();
}

BOOL CGraphicSaveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CGraphicSaveView ����

void CGraphicSaveView::OnDraw(CDC* pDC)
{
	CGraphicSaveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	HMETAFILE hMetaFile;
	hMetaFile=m_dcMetaFile.Close();
	pDC->PlayMetaFile(hMetaFile);
	m_dcMetaFile.Create();
	m_dcMetaFile.PlayMetaFile(hMetaFile);
	DeleteMetaFile(hMetaFile);
}


// CGraphicSaveView ��ӡ


void CGraphicSaveView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CGraphicSaveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGraphicSaveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGraphicSaveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGraphicSaveView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicSaveView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGraphicSaveView ���

#ifdef _DEBUG
void CGraphicSaveView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicSaveView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicSaveDoc* CGraphicSaveView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicSaveDoc)));
	return (CGraphicSaveDoc*)m_pDocument;
}
#endif //_DEBUG



void CGraphicSaveView::OnDot()
{
	// TODO: �ڴ���������������
	m_nDrawType=1;
}

void CGraphicSaveView::OnLine()
{
	// TODO: �ڴ���������������
	m_nDrawType=2;
}

void CGraphicSaveView::OnRect()
{
	// TODO: �ڴ���������������
	m_nDrawType=3;
}

void CGraphicSaveView::OnEllispe()
{
	// TODO: �ڴ���������������
	m_nDrawType=4;
}

void CGraphicSaveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptOrigin=point;
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGraphicSaveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	//dc.SelectObject(pBrush);
	m_dcMetaFile.SelectObject(pBrush);

	switch(m_nDrawType)
	{
	case 1:
		//dc.SetPixel(point,RGB(0,0,0));
		m_dcMetaFile.SetPixel(point,RGB(0,0,0));
		break;
	case 2:
		//dc.MoveTo(m_ptOrigin);
		//dc.LineTo(point);
		m_dcMetaFile.MoveTo(m_ptOrigin);
		m_dcMetaFile.LineTo(point);
		break;;
	case 3:
		//dc.Rectangle(CRect(m_ptOrigin,point));
		m_dcMetaFile.Rectangle(CRect(m_ptOrigin,point));
		break;
	case 4:
		//dc.Ellipse(CRect(m_ptOrigin,point));
		m_dcMetaFile.Ellipse(CRect(m_ptOrigin,point));
		break;
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CGraphicSaveView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CScrollView::OnPaint()
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CGraphicSaveView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	SetScrollSizes(MM_TEXT,CSize(800,600));
}

void CGraphicSaveView::OnFileOpen()
{
	// TODO: �ڴ���������������
	HMETAFILE hMetaFile;
	hMetaFile=GetMetaFile(_T("meta.wmf"));
	m_dcMetaFile.PlayMetaFile(hMetaFile);
	DeleteMetaFile(hMetaFile);
	Invalidate();
}

void CGraphicSaveView::OnFileSave()
{
	HMETAFILE hMetaFile;
	hMetaFile=m_dcMetaFile.Close();
	CopyMetaFile(hMetaFile,_T("meta.wmf"));
	m_dcMetaFile.Create();
	DeleteMetaFile(hMetaFile);
}
