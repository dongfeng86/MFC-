
// SerializeView.cpp : CSerializeView ���ʵ��
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
	// ��׼��ӡ����
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

// CSerializeView ����/����

CSerializeView::CSerializeView()
{
	// TODO: �ڴ˴���ӹ������
	m_nDrawType=0;
	m_ptOrigin=0;

}

CSerializeView::~CSerializeView()
{
}

BOOL CSerializeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSerializeView ����

void CSerializeView::OnDraw(CDC* pDC)
{
	CSerializeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	int iCount;
	iCount=pDoc->m_obArray.GetSize();
	for(int i=0;i<iCount;i++)
	{
		//((CGraph*)m_obArray.GetAt(i))->Draw(pDC);
		((CGraph*)pDoc->m_obArray.GetAt(i))->Draw(pDC);
	}
}


// CSerializeView ��ӡ


void CSerializeView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSerializeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSerializeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSerializeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CSerializeView ���

#ifdef _DEBUG
void CSerializeView::AssertValid() const
{
	CView::AssertValid();
}

void CSerializeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSerializeDoc* CSerializeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSerializeDoc)));
	return (CSerializeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSerializeView ��Ϣ�������

//void CSerializeView::OnWrite()
//{
//	// TODO: �ڴ���������������
//	CFile file(_T("1.txt"),CFile::modeCreate|CFile::modeWrite);
//	//����浵����
//	CArchive ar(&file,CArchive::store);
//	int i=4;
//	char ch='a';
//	float f=1.3f;
//	CString str("http://www.sunxin.org");
//	//��������
//	ar<<i<<ch<<f<<str;
//}

//void CSerializeView::OnRead()
//{
//	// TODO: �ڴ���������������
//	CFile file(_T("1.txt"),CFile::modeRead);
//	CArchive ar(&file,CArchive::load);
//	int i;
//	char ch;
//	float f;
//	CString str;
//	CString strResult;
//	//��ȡ����
//	ar>>i>>ch>>f>>str;
//	strResult.Format(_T("%d,%c,%f,%s"),i,ch,f,str);
//	MessageBox(strResult);
//}

void CSerializeView::OnDot()
{
	// TODO: �ڴ���������������
	m_nDrawType=1;
}

void CSerializeView::OnLine()
{
	// TODO: �ڴ���������������
	m_nDrawType=2;
}

void CSerializeView::OnRect()
{
	// TODO: �ڴ���������������
	m_nDrawType=3;
}

void CSerializeView::OnEllispe()
{
	// TODO: �ڴ���������������
	m_nDrawType=4;
}

void CSerializeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptOrigin=point;

	CView::OnLButtonDown(nFlags, point);
}

void CSerializeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
