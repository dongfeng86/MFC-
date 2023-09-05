// TCPClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Winsock2.h>
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	//加载套接字库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return EXIT_SUCCESS;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup();
		return EXIT_SUCCESS;
	}

	//第一步：创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	//第二部：向服务器发送连接请求
	SOCKADDR_IN addrSrv;
	//地址127.0.0.1 是本地回路地址。主机环回是指地址为 127.0.0.1 的任何数据包
	//都不应该离开计算机（主机），发送它——而不是被发送到本地网络或互联网，它只是被自己“环回”，
	//并且发送数据包的计算机成为接收者。
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//第三步：和服务器进行通信
	//接受数据
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);
	//发送数据
	send(sockClient, "This is lisi", strlen("This is lisi") + 1, 0);

	//第四步：关闭套接字
	closesocket(sockClient);

	//释放资源
	WSACleanup();
	getchar();
}