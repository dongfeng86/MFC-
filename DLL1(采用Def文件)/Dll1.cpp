#include <Windows.h>
#include <atlstr.h>
#include "Dll1.h"

int add(int a,int b)
{
	return a+b;
}

int subtract(int a ,int b)
{
	return a-b;
}

Point::Point()
{
	m_dXPoint = 0;
	m_dYPoint = 0;
}

Point::~Point()
{
	m_dXPoint = 0;
	m_dYPoint = 0;
}

void Point::OutPut(int x,int y)
{
	HWND hwnd=GetForegroundWindow();
	HDC hdc=GetDC(hwnd);
	CString str;
	str.Format(_T("x=%d,y=%d"),x,y);
	TextOut(hdc,0,0,str,wcslen(str));
	ReleaseDC(hwnd,hdc);
}