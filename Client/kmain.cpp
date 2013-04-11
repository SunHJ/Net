#include <iostream>

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define SERVPORT 8989 /*服务器监听端口号*/
#define DEST_IP  "127.0.0.1"
#define MAXDATASIZE 100

int main(int argc, char* argv[])
{
	SOCKET sockfd;

	int nRetCode, recvbytes = 0; 
	char buf[MAXDATASIZE] = {0x06, 0x00, 0x16, 0x16, 0x13, 0x61, 0x62, 0x63}; 

	//struct hostent *host; 
	struct sockaddr_in serv_addr; /* 目的地址*/  
	//struct sockaddr_in dest_addr; 

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (0 != err)
	{
		cout<<"Socket failed";
		return 0;
	}
	if (LOBYTE(wsaData.wVersion)!= 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		return 0;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket创建出错！");
		exit(1);
	}

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(SERVPORT); 
	/*	serv_addr.sin_addr = *((struct in_addr *)host->h_addr);*/
	serv_addr.sin_addr.s_addr = inet_addr(DEST_IP);  
	memset( &(serv_addr.sin_zero), 0, 8);

	nRetCode = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));

	if (nRetCode == -1) 
	{ 
			perror("connect出错！");
			//exit(1);
	}

	char szMsg[] = "ni hao";
	int nlen = sizeof(serv_addr);
	int uIndex = 0;
	while (1)
	{
		Sleep(1000);
		if (send(sockfd, buf, ::strlen(buf), 0) == -1)		
		{
			cout<<WSAGetLastError()<<endl;
		}
		else
		{
			cout<<uIndex++<<":an TCP package is sended"<<endl;
		}
		if ((recvbytes=recv(sockfd, buf, MAXDATASIZE, 0)) !=-1)
		{ 
			buf[recvbytes] = '\0'; 
			printf( "Received: %s",buf);
		}

	}

	closesocket(sockfd); 

	return 0;
}
