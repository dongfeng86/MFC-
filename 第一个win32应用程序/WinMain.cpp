/*���ļ��ǲ���win32�ӿ����ĶԻ�����Ҫ��Ϊ�����mfc�����л���*/
#include<Windows.h>
#include<stdio.h>
#include <tchar.h>
#include <atlstr.h>


LRESULT CALLBACK WinSunProc(HWND hwnd,                //���ھ��
							UINT uMag,                //��Ϣ��
							WPARAM wParam,            //��Ϣ��һ�����Ӳ���
							LPARAM lParam             //��Ϣ��2����������
							);

int WINAPI WinMain( __in HINSTANCE hInstance,         //��ǰ��ʵ�����
				   __in_opt HINSTANCE hPrevInstance,  //֮ǰ�ľ��
				   __in_opt LPSTR lpCmdLine,          //�����в���
				   __in int nShowCmd                  // 
				   )
{
	//���ȣ�Ӧ�����һ��������
	WNDCLASS wndClass;
	wndClass.cbClsExtra=0;                           //�����฽���ڴ�
	wndClass.cbWndExtra=0;                           //���ڸ����ڴ�
	wndClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor=LoadCursor(NULL,IDC_CROSS);
	wndClass.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndClass.hInstance=hInstance;                    //Ӧ�ó���ʵ�������WinMain����������
	wndClass.lpfnWndProc=WinSunProc;                 //���ڹ��̺����ĵ��õ�ַ
	wndClass.lpszClassName=_T("sunxin");             //�����������
	wndClass.lpszMenuName=NULL;                      //�˵�����
	wndClass.style=CS_HREDRAW|CS_VREDRAW;

	//������������ע�������ϵͳ
	RegisterClass(&wndClass);

	//�������ڣ�����һ�������������洴���Ĵ��ڵľ��
	HWND hwnd;
	hwnd=CreateWindow(_T("sunxin"),_T("���,�ҵĵ�һ������"),WS_OVERLAPPEDWINDOW,
		0,0,600,400,NULL,NULL,hInstance,NULL);
	
	//��ʾ��ˢ�´���
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	//������Ϣ�ṹ�壬��ʼ��Ϣѭ��
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//��д���ڹ��̺���
LRESULT CALLBACK WinSunProc(HWND hwnd, /*���ھ�� */ UINT uMag, /*��Ϣ�� */ WPARAM wParam, /*��Ϣ��һ�����Ӳ��� */ LPARAM lParam /*��Ϣ��2���������� */)
{
	switch(uMag)
	{
	case WM_CHAR:
		{
		CString str;                                            //�����и�������˼�����飬�������case��ǩ��������������Ҫ��{}������
		str.Format(_T("char code is %d"),wParam);
		MessageBox(hwnd,str,_T("char"),0);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd,_T("mouse clicked"),_T("message"),0);
		HDC hdc;
		hdc=GetDC(hwnd);
		TextOut(hdc,0,50,_T("����Ա֮��"),wcslen(_T("����Ա֮��")));
		ReleaseDC(hwnd,hdc);                                          //�����ͷ��豸��������Դ
		break;
	case WM_PAINT:
		HDC hDc;
		PAINTSTRUCT ps;
		hDc=BeginPaint(hwnd,&ps);                                    //BeginPaintֻ������ӦWM_PAINT��Ϣʱ����
		TextOut(hdc,0,0,_T("http://www.sunxin.org"),wcslen(_T("http://www.sunxin.org")));
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(hwnd,_T("�Ƿ���Ľ�����"),_T("message"),MB_YESNO))
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


