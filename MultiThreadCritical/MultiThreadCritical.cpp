// MultiThreadCritical.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>
#include <iostream>

int iTickets = 1000;

CRITICAL_SECTION g_cs;

//线程1的入口函数
DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter)
{
	while (true)
	{
		//等待获取关键段对象
		EnterCriticalSection(&g_cs);
		if (iTickets > 0)
		{
			std::cout << "thread1 sell tickes:" << iTickets-- << std::endl;
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			LeaveCriticalSection(&g_cs);
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
		//等待获取关键段对象
		EnterCriticalSection(&g_cs);
		if (iTickets > 0)
		{
			std::cout << "thread2 sell tickes:" << iTickets-- << std::endl;
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
	}

	return 0;
}

int main()
{
	//创建线程
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	InitializeCriticalSection(&g_cs);

	//以下代码为了防止主线程提前退出，从而使进程退出，也就终止了进程下所有线程的运行
	while (true)
	{
		if (iTickets > 0)
			Sleep(200);
		else
		{
			//释放关键代码段对象
			DeleteCriticalSection(&g_cs);
			getchar();
			return 0;
		}
	}
}
