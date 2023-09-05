// MultiThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<windows.h>

DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter);
DWORD WINAPI Fun2Proc(__in  LPVOID lpParameter);


int iIndx = 0;
int iTickets = 100;
HANDLE hMutex;

//创建进程的时候，系统会自动创建进程的第一个线程，成为主线程，也就是
//执行main函数的进程
int main()
{
	HANDLE hThread1;
	HANDLE hThread2;

	//创建互斥对象
	hMutex = CreateMutex(NULL, FALSE, NULL);

	//创建线程
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	while (true)
	{
		if (iTickets > 0)
			Sleep(100);
		else
		{
			getchar();
			return 0;
		}
	}
}

//
DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (iTickets > 0)
		{
			std::cout << "thread1 sell tickets:" << iTickets-- << std::endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI Fun2Proc(__in  LPVOID lpParameter)
{

	while (true)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (iTickets > 0)
		{
			std::cout << "thread2 sell tickets:" << iTickets-- << std::endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}
	return 0;
}