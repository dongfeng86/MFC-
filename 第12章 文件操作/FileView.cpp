
// FileView.cpp : CFileView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFileView::OnFilePrintPreview)
	ON_COMMAND(ID_WRITE, &CFileView::OnWrite)
	ON_COMMAND(ID_READ, &CFileView::OnRead)
END_MESSAGE_MAP()

// CFileView ����/����

CFileView::CFileView()
{
	// TODO: �ڴ˴���ӹ������

}

CFileView::~CFileView()
{
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFileView ����

void CFileView::OnDraw(CDC* /*pDC*/)
{
	CFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CFileView ��ӡ


void CFileView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CFileView ���

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileDoc* CFileView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileDoc)));
	return (CFileDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileView ��Ϣ�������

void CFileView::OnWrite()
{
	//��ʽ1��C���Զ�д�ļ��ķ�ʽ
	//FILE* pFile=fopen("ansi.txt","w");
	//fwrite("https://www.baidu.com/",sizeof(char),strlen("https://www.baidu.com/"),pFile);
	//fseek(pFile,0,SEEK_SET);
	//fwrite("ftp:",sizeof(char),strlen("ftp:"),pFile);
	//fflush(pFile);
	//fclose(pFile);

	//��ʽ2��C++д���ļ�
	//std::ofstream ofs("4.txt");
	//ofs.write("https://www.baidu.com��/",strlen("https://www.baidu.com��/"));
	//ofs.close();

	//��ʽ3����Win32��api
	//HANDLE hFile;
	//hFile=CreateFile(_T("5.txt"),GENERIC_WRITE,0,NULL,CREATE_NEW,
	//	FILE_ATTRIBUTE_NORMAL,NULL);
	//DWORD dwWrite;
	//TCHAR ch[]=_T("https://www.baidu.com/��");
	//WriteFile(hFile,ch,wcslen(ch)*sizeof(TCHAR),&dwWrite,NULL);
	//CloseHandle(hFile);

	//����MFC��ʵ���ļ���д
	CFile file(_T("6.txt"),CFile::modeCreate | CFile::modeWrite);
	file.Write(_T("https://www.baidu.com/��"),wcslen(_T("https://www.baidu.com/��"))*sizeof(TCHAR));
	file.Close();

}

void CFileView::OnRead()
{
	//C���Զ��ļ��ķ�ʽ
	//FILE* pFile=fopen("ansi.txt","r");
	//char* pBuf;
	//fseek(pFile,0,SEEK_END);	//�ƶ��ļ�ָ�뵽��β,ע�⣬�ļ���һ���ֽڱ��Ϊ0���þ佫��ָ��������ļ��������һ���ֽڵ���һ��λ��
	//int len=ftell(pFile);
	//rewind(pFile);		//���·����ļ�ָ�뵽��ʼ��
	//pBuf=new char[len+1];
	//pBuf[len]=0;
	//fread(pBuf,sizeof(char),len,pFile);
	//CString str=CA2T(pBuf);
	//MessageBox(str);
	//fclose(pFile);
	//delete[] pBuf;

	//��ʽ2��C++��ȡ�ļ�
	//std::ifstream ifs("4.txt");
	//char ch[100]={0};
	//ifs.read(ch,100);
	//ifs.close();
	//CString str=CA2T(ch);
	//MessageBox(str);

	//��ʽ3��Win32��api���ж�ȡ
	//HANDLE hFile;
	//hFile=CreateFile(_T("5.txt"),GENERIC_READ,0,NULL,OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,NULL);
	//TCHAR ch[100];
	//DWORD dwReads;
	//ReadFile(hFile,ch,100,&dwReads,NULL);
	//ch[dwReads/sizeof(TCHAR)]=0;		//���ַ���ĩβ����Ϊ0
	//CloseHandle(hFile);
	//MessageBox(ch);

	//��ʽ4������MFC��
	CFile file(_T("6.txt"),CFile::modeRead);
	TCHAR* pBuf;
	DWORD dwFileLen;
	dwFileLen=file.GetLength();
	//pBuf=new char[dwFileLen+1];
	pBuf=new TCHAR[dwFileLen/sizeof(TCHAR)+1];
	file.Read(pBuf,dwFileLen);
	pBuf[dwFileLen/sizeof(TCHAR)]=0;
	file.Close();
	MessageBox(pBuf);
	delete pBuf;
}
