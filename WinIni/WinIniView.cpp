
// WinIniView.cpp : CWinIniView ���ʵ��
//

#include "stdafx.h"
#include "WinIni.h"

#include "WinIniDoc.h"
#include "WinIniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinIniView

IMPLEMENT_DYNCREATE(CWinIniView, CView)

BEGIN_MESSAGE_MAP(CWinIniView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinIniView::OnFilePrintPreview)
	ON_COMMAND(ID_WRITEREG, &CWinIniView::OnWritereg)
	ON_COMMAND(ID_READREG, &CWinIniView::OnReadreg)
END_MESSAGE_MAP()

// CWinIniView ����/����

CWinIniView::CWinIniView()
{
	// TODO: �ڴ˴���ӹ������

}

CWinIniView::~CWinIniView()
{
}

BOOL CWinIniView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CWinIniView ����

void CWinIniView::OnDraw(CDC* /*pDC*/)
{
	CWinIniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CWinIniView ��ӡ


void CWinIniView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CWinIniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CWinIniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CWinIniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CWinIniView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinIniView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CWinIniView ���

#ifdef _DEBUG
void CWinIniView::AssertValid() const
{
	CView::AssertValid();
}

void CWinIniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinIniDoc* CWinIniView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinIniDoc)));
	return (CWinIniDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinIniView ��Ϣ�������

void CWinIniView::OnWritereg()
{
	// TODO: �ڴ���������������
	HKEY hKey;
	DWORD dwAge=30;
	RegCreateKey(HKEY_LOCAL_MACHINE,_T("SoftWare\\helloNew\\admin"),
		&hKey);
	RegSetValue(hKey,NULL,REG_SZ,_T("zhangsan"),wcslen(_T("zhangsan")));
	RegSetValueEx(hKey,_T("age"),0,REG_DWORD,(const BYTE*)&dwAge,4);
	RegCloseKey(hKey);

}

void CWinIniView::OnReadreg()
{
	// TODO: �ڴ���������������
	//long lValue;
	//RegQueryValue(HKEY_LOCAL_MACHINE,_T("SoftWare\\helloNew\\admin"),
	//	NULL,&lValue);
	//TCHAR* pBuf=new TCHAR[lValue];
	//RegQueryValue(HKEY_LOCAL_MACHINE,_T("SoftWare\\helloNew\\admin"),
	//	pBuf,&lValue);
	//MessageBox(pBuf);

	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,_T("SoftWare\\helloNew\\admin"),&hKey);
	DWORD dwType;
	DWORD dwValue;
	DWORD dwAge;
	RegQueryValueEx(hKey,_T("age"),0,&dwType,(LPBYTE)&dwAge,&dwValue);
	CString str;
	str.Format(_T("age=%d"),dwAge);
	MessageBox(str);
}
