// TCPSrv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Winsock2.h>
#include <iostream>
#include <ws2tcpip.h>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return EXIT_SUCCESS;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup();
		return EXIT_SUCCESS;
	}


	//第一步：创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	//第二步：将套接字绑定到本地地址和端口上
	SOCKADDR_IN addSrv;
	//使用网络字节序，可以将IP地址指定为INADDR_ANY，允许套接字向任何分配给
	//本地机器的IP地址发送或接受数据。
	//如果我们想让套接字使用多个IP中的一个地址，就必须指定实际地址，这需要用到
	//inet_addr函数来实现
	addSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addSrv.sin_family = AF_INET;
	addSrv.sin_port = htons(6000);	
	bind(sockSrv, (SOCKADDR*)&addSrv, sizeof(SOCKADDR));//绑定套接字

	//第三步：将套接字设为监听模式，准备接受客户请求,
	//第二个参数是指等待连接队列的最大长度，比如说此时等待连接队列是5，那么下一个连接请求会被拒绝
	listen(sockSrv, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (true)
	{
		//第四步：等待客户连接到来
		//accept 函数提取套接字 s 上挂起连接队列上的第一个连接。然后，它会创建一个新的套接字，并将其句柄并将其返回。
		//新创建的套接字是将处理实际连接的套接字;它具有与套接字相同的属性，包括使用 WSAAsyncSelect 或 WSAEventSelect 函数注册的异步事件。
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[100];
		sprintf_s(sendBuf, "Welcome %s to http://www.sunxin.org", inet_ntoa(addrClient.sin_addr));

		//第五步：用返回的套接字和客户端通信
		//发送数据，为了让接收端在接受数据以后，可以在该数据字符串之后增加一个“\0”结尾标志
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[100];
		//接收数据
		recv(sockConn, recvBuf, 100, 0);

		//打印接受到的数据
		printf("%s\n", recvBuf);
		//第六步：关闭套接字，此时程序进入到下一循环
		closesocket(sockConn);
	}
}
