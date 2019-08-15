/*本文件是采用win32接口做的对话框，主要是为了理解mfc的运行机制*/
#include<Windows.h>
#include<stdio.h>
#include <tchar.h>
#include <atlstr.h>


LRESULT CALLBACK WinSunProc(HWND hwnd,                //窗口句柄
							UINT uMag,                //消息号
							WPARAM wParam,            //消息第一个附加参数
							LPARAM lParam             //消息第2个附件参数
							);

int WINAPI WinMain( __in HINSTANCE hInstance,         //当前的实例句柄
				   __in_opt HINSTANCE hPrevInstance,  //之前的句柄
				   __in_opt LPSTR lpCmdLine,          //命令行参数
				   __in int nShowCmd                  // 
				   )
{
	//首先，应当设计一个窗口类
	WNDCLASS wndClass;
	wndClass.cbClsExtra=0;                           //窗口类附加内存
	wndClass.cbWndExtra=0;                           //窗口附加内存
	wndClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor=LoadCursor(NULL,IDC_CROSS);
	wndClass.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndClass.hInstance=hInstance;                    //应用程序实例句柄由WinMain函数传进来
	wndClass.lpfnWndProc=WinSunProc;                 //窗口过程函数的调用地址
	wndClass.lpszClassName=_T("sunxin");             //窗口类的名字
	wndClass.lpszMenuName=NULL;                      //菜单名称
	wndClass.style=CS_HREDRAW|CS_VREDRAW;

	//接下来，把类注册给操作系统
	RegisterClass(&wndClass);

	//创建窗口，定义一个变量用来保存创建的窗口的句柄
	HWND hwnd;
	hwnd=CreateWindow(_T("sunxin"),_T("你好,我的第一个窗口"),WS_OVERLAPPEDWINDOW,
		0,0,600,400,NULL,NULL,hInstance,NULL);
	
	//显示及刷新窗口
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//定义消息结构体，开始消息循环
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//编写窗口过程函数
LRESULT CALLBACK WinSunProc(HWND hwnd, /*窗口句柄 */ UINT uMag, /*消息号 */ WPARAM wParam, /*消息第一个附加参数 */ LPARAM lParam /*消息第2个附件参数 */)
{
	switch(uMag)
	{
	case WM_CHAR:
		{
		CString str;                                            //这里有个很有意思的事情，如果想在case标签下声明变量，需要用{}括起来
		str.Format(_T("char code is %d"),wParam);
		MessageBox(hwnd,str,_T("char"),0);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd,_T("mouse clicked"),_T("message"),0);
		HDC hdc;
		hdc=GetDC(hwnd);
		TextOut(hdc,0,50,_T("程序员之家"),wcslen(_T("程序员之家")));
		ReleaseDC(hwnd,hdc);                                          //必须释放设备描述表资源
		break;
	case WM_PAINT:
		HDC hDc;
		PAINTSTRUCT ps;
		hDc=BeginPaint(hwnd,&ps);                                    //BeginPaint只能在响应WM_PAINT消息时调用
		TextOut(hdc,0,0,_T("http://www.sunxin.org"),wcslen(_T("http://www.sunxin.org")));
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(hwnd,_T("是否真的结束？"),_T("message"),MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMag,wParam,lParam);
	}
	return 0;
}


