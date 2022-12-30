
// FileView.cpp : CFileView 类的实现
//

#include "stdafx.h"
#include "File.h"

#include "FileDoc.h"
#include "FileView.h"
#include <atlconv.h>
#include <AtlBase.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileView

IMPLEMENT_DYNCREATE(CFileView, CView)

BEGIN_MESSAGE_MAP(CFileView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFileView::OnFilePrintPreview)
	ON_COMMAND(ID_WRITE, &CFileView::OnWrite)
	ON_COMMAND(ID_READ, &CFileView::OnRead)
END_MESSAGE_MAP()

// CFileView 构造/析构

CFileView::CFileView()
{
	// TODO: 在此处添加构造代码

}

CFileView::~CFileView()
{
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFileView 绘制

void CFileView::OnDraw(CDC* /*pDC*/)
{
	CFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFileView 打印


void CFileView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CFileView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CFileView 诊断

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileDoc* CFileView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileDoc)));
	return (CFileDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileView 消息处理程序

void CFileView::OnWrite()
{
	//方式1：C语言读写文件的方式
	//FILE* pFile=fopen("ansi.txt","w");
	//fwrite("https://www.baidu.com/",sizeof(char),strlen("https://www.baidu.com/"),pFile);
	//fseek(pFile,0,SEEK_SET);
	//fwrite("ftp:",sizeof(char),strlen("ftp:"),pFile);
	//fflush(pFile);
	//fclose(pFile);

	//方式2：C++写入文件
	//std::ofstream ofs("4.txt");
	//ofs.write("https://www.baidu.com我/",strlen("https://www.baidu.com我/"));
	//ofs.close();

	//方式3：用Win32的api
	//HANDLE hFile;
	//hFile=CreateFile(_T("5.txt"),GENERIC_WRITE,0,NULL,CREATE_NEW,
	//	FILE_ATTRIBUTE_NORMAL,NULL);
	//DWORD dwWrite;
	//TCHAR ch[]=_T("https://www.baidu.com/我");
	//WriteFile(hFile,ch,wcslen(ch)*sizeof(TCHAR),&dwWrite,NULL);
	//CloseHandle(hFile);

	//利用MFC类实现文件读写
	//CFile file(_T("6.txt"),CFile::modeCreate | CFile::modeWrite);
	//file.Write(_T("https://www.baidu.com/我"),wcslen(_T("https://www.baidu.com/我"))*sizeof(TCHAR));
	//file.Close();
	////在文本文档中写入ANSI编码（GBK）的字符
	//CFile file2(_T("7.txt"),CFile::modeCreate|CFile::modeWrite);
	//file2.Write("https://www.baidu.com/我",strlen("https://www.baidu.com/我"));
	//file2.Close();

	//利用打开对话框实现文件写入
	CFileDialog dlgOpen(FALSE);
	dlgOpen.m_ofn.lpstrTitle=_T("我的文件保存对话框");
	dlgOpen.m_ofn.lpstrFilter=_T("绘图文件(*.dwg)\0*.dwg\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	dlgOpen.m_ofn.lpstrDefExt=_T("txt");

	if(IDOK==dlgOpen.DoModal())
	{
		CFile file(dlgOpen.GetPathName(),CFile::modeCreate|CFile::modeWrite);
		//file.Write(_T("https://www.baidu.com/我"),wcslen(_T("https://www.baidu.com/我"))*sizeof(TCHAR));
		file.Write("https://www.baidu.com/我",strlen("https://www.baidu.com/我")*sizeof(CHAR));
		file.Close();
	}
}

void ReadPixel()
{
	//在win10下验证，只要是是16：9类型（自己的笔记本屏幕是16:9的）的分辨率，
	//屏幕尺寸是屏幕显示的范围
	//逻辑像素就是所选择的分辨率。
	//每逻辑英寸像素点数和缩放与比例的设置有关：
	//当缩放比例为100%时，每逻辑英寸像素点数为96；125%→120；150%→144；175%→168；220%→211
	//计算公式为：96*缩放比例=每逻辑英寸像素点数

	HDC hDc = ::GetDC(HWND(NULL));

	//屏幕的尺寸（和屏幕实际显示的范围相关）
	int iScreenWidth = ::GetDeviceCaps(hDc, HORZSIZE);
	int iScreenHgt = ::GetDeviceCaps(hDc, VERTSIZE);

	//逻辑像素数(和选择的分辨率相同)
	int pagecx = ::GetDeviceCaps(hDc, HORZRES);
	int pagecy = ::GetDeviceCaps(hDc, VERTRES);

	//每逻辑英寸像素点数（和缩放比例相关,具体来说，是缩放比例×96）
	short cxInch = ::GetDeviceCaps(hDc, LOGPIXELSX);
	short cyInch = ::GetDeviceCaps(hDc, LOGPIXELSY);

	::ReleaseDC(HWND(NULL), hDc);
}

void CFileView::OnRead()
{
	ReadPixel();

	//C语言读文件的方式
	//FILE* pFile=fopen("ansi.txt","r");
	//char* pBuf;
	//fseek(pFile,0,SEEK_END);	//移动文件指针到结尾,注意，文件第一个字节编号为0；该句将流指针放置于文件内容最后一个字节的下一个位置
	//int len=ftell(pFile);
	//rewind(pFile);		//重新放置文件指针到开始处
	//pBuf=new char[len+1];
	//pBuf[len]=0;
	//fread(pBuf,sizeof(char),len,pFile);
	//CString str=CA2T(pBuf);
	//MessageBox(str);
	//fclose(pFile);
	//delete[] pBuf;

	//方式2：C++读取文件
	//std::ifstream ifs("4.txt");
	//char ch[100]={0};
	//ifs.read(ch,100);
	//ifs.close();
	//CString str=CA2T(ch);
	//MessageBox(str);

	//方式3：Win32中api进行读取
	//HANDLE hFile;
	//hFile=CreateFile(_T("5.txt"),GENERIC_READ,0,NULL,OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,NULL);
	//TCHAR ch[100];
	//DWORD dwReads;
	//ReadFile(hFile,ch,100,&dwReads,NULL);
	//ch[dwReads/sizeof(TCHAR)]=0;		//将字符串末尾设置为0
	//CloseHandle(hFile);
	//MessageBox(ch);

	//方式4：利用MFC类读取UCS-2编码的文件，这个例子非常精彩
	//字符串末尾的0到底占据1个或者2个字符，完全是根据字符是
	//char类型还是wchar_t类型
	//CFile file(_T("6.txt"),CFile::modeRead);
	//TCHAR* pBuf;
	//DWORD dwFileLen;
	//dwFileLen=file.GetLength();
	////pBuf=new char[dwFileLen+1];
	//pBuf=new TCHAR[dwFileLen/sizeof(TCHAR)+1];
	//file.Read(pBuf,dwFileLen);
	//pBuf[dwFileLen/sizeof(TCHAR)]=0;
	//file.Close();
	//MessageBox(pBuf);
	//delete pBuf;

	//利用打开对话框实现文件打开
	CFileDialog dlgOpen(TRUE);
	dlgOpen.m_ofn.lpstrTitle=_T("我的文件打开对话框");
	dlgOpen.m_ofn.lpstrFilter=_T("绘图文件(*.dwg)\0*.dwg\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	dlgOpen.m_ofn.lpstrDefExt=_T("txt");

	if(IDOK==dlgOpen.DoModal())
	{
		CFile file(dlgOpen.GetPathName(),CFile::modeRead);
		TCHAR* pBuf;
		DWORD dwFileLen;
		dwFileLen=file.GetLength();
		pBuf=new TCHAR[dwFileLen/sizeof(TCHAR)+1];
		file.Read(pBuf,dwFileLen);
		pBuf[dwFileLen/sizeof(TCHAR)]=0;
		file.Close();
		MessageBox(pBuf);
		delete pBuf;
	}
}
