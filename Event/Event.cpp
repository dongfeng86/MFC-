// Event.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>
#include <iostream>

HANDLE g_hEvent;
int iTickets = 1000;

//线程1的入口函数
DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter)
{
	while (true)
	{
		//请求事件对象
		WaitForSingleObject(g_hEvent, INFINITE);
		if (iTickets > 0)
		{
			std::cout << "thread1 sell tickes:" << iTickets-- << std::endl;
			SetEvent(g_hEvent);
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}

	return 0;
}

//线程2的入口函数
DWORD WINAPI Fun2Proc(__in  LPVOID lpParameter)
{
	while (true)
	{
		//请求事件对象
		WaitForSingleObject(g_hEvent, INFINITE);
		if (iTickets > 0)
		{
			std::cout << "thread2 sell tickes:" << iTickets-- << std::endl;
			SetEvent(g_hEvent);
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}

	return 0;
}

int main()
{
	HANDLE hThread1;
	HANDLE hThread2;

	//创建人工重置事件内核对象
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetEvent(g_hEvent);

	//创建线程
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	//以下代码为了防止主线程提前退出，从而使进程退出，也就终止了进程下所有线程的运行
	while (true)
	{
		if (iTickets > 0)
			Sleep(200);
		else
		{
			//关闭事件对象句柄
			CloseHandle(g_hEvent);
			getchar();
			return 0;
		}
	}
}
