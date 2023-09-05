// MultiThread.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include<windows.h>

DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter);
DWORD WINAPI Fun2Proc(__in  LPVOID lpParameter);

int iIndx = 0;
int iTickets = 100;

//�������̵�ʱ��ϵͳ���Զ��������̵ĵ�һ���̣߳���Ϊ���̣߳�Ҳ����
//ִ��main�����Ľ���
int main()
{
	HANDLE hThread1;
	HANDLE hThread2;

	//�����߳�
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	while (true)
		if (iTickets > 0)
			Sleep(100);
		else
		{
			getchar();
			return 0;
		}
}

//
DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter)
{
	while (true)
	{
		if (iTickets > 0)
			std::cout << "thread1 sell tickets:" << iTickets-- << std::endl;
		else
			break;
	}

	return 0;
}

DWORD WINAPI Fun2Proc(__in  LPVOID lpParameter)
{

	while (true)
	{
		if (iTickets > 0)
			std::cout << "thread2 sell tickets:" << iTickets-- << std::endl;
		else
			break;
	}
	return 0;
}