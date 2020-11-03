
// WinIniView.cpp : CWinIniView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinIniView::OnFilePrintPreview)
	ON_COMMAND(ID_WRITEREG, &CWinIniView::OnWritereg)
	ON_COMMAND(ID_READREG, &CWinIniView::OnReadreg)
END_MESSAGE_MAP()

// CWinIniView 构造/析构

CWinIniView::CWinIniView()
{
	// TODO: 在此处添加构造代码

}

CWinIniView::~CWinIniView()
{
}

BOOL CWinIniView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CWinIniView 绘制

void CWinIniView::OnDraw(CDC* /*pDC*/)
{
	CWinIniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CWinIniView 打印


void CWinIniView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CWinIniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CWinIniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CWinIniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CWinIniView 诊断

#ifdef _DEBUG
void CWinIniView::AssertValid() const
{
	CView::AssertValid();
}

void CWinIniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinIniDoc* CWinIniView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinIniDoc)));
	return (CWinIniDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinIniView 消息处理程序

void CWinIniView::OnWritereg()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
