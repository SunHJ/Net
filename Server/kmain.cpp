#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define SERVPORT	8989 /*服务器监听端口号*/
#define MAXDATASIZE 100
#define BACKLOG		10
std::vector<SOCKET> client_fd;
char buf[MAXDATASIZE];
DWORD WINAPI qtPingServerThreadFunc(LPVOID lpThreadParameter);

int main(int argc, char* argv[])
{
	SOCKET sockfd; /*sock_fd：监听socket；client_fd：数据传输socket */ 

	struct sockaddr_in my_addr; /* 本机地址信息*/

	struct sockaddr_in remote_addr; /* 客户端地址信息*/ 

	char szMsg[]="hello";
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 0);

	err = WSAStartup(wVersionRequested,&wsaData);
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
	if (INVALID_SOCKET == sockfd)
	{
		cout<<"Soket Create Failed";
		return 0;
	}

	/*sockfd = socket(AF_INET, SOCK_STREAM, 0);*/
	if (sockfd == -1) 
	{ 
		perror( "socket创建出错！"); 
		exit(1);
	} 

	my_addr.sin_family = AF_INET; 
	my_addr.sin_port = htons(SERVPORT); 
	my_addr.sin_addr.s_addr = INADDR_ANY; 
	memset( &(my_addr.sin_zero),0,8);
	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror( "bind出错！");
		//exit(1); 
	} 
	int nRetCode = 0;
	//unsigned long ulOption = 1;
	//::ioctlsocket(sockfd, FIONBIO, &ulOption);

	int n = 0;
	while(1)
	{ 
		if (listen(sockfd, BACKLOG) != -1) 
		{ 
			int sin_size = sizeof(struct sockaddr_in); 
			SOCKET nSocket = accept(sockfd, (struct sockaddr *) &remote_addr, &sin_size);
			std::vector<SOCKET>::iterator itr_end = client_fd.end();
			std::vector<SOCKET>::iterator itr = std::find(client_fd.begin(),itr_end,nSocket);
			if (itr == itr_end)
			{
				client_fd.push_back(nSocket);
				printf( "received a connection from %s\n", inet_ntoa(remote_addr.sin_addr));
				DWORD dwPingThreadID;
				HANDLE hPingHandle = CreateThread(0, 0, qtPingServerThreadFunc, 0, 0, &dwPingThreadID);
			}
		}
	}

	for (size_t n = 0;n < client_fd.size(); n++)
	{
		closesocket(client_fd[n]); 
	}
	client_fd.clear();
} 

DWORD WINAPI qtPingServerThreadFunc(LPVOID lpThreadParameter)
{
	while (true)
	{
		for (size_t n = 0;n < client_fd.size(); n++)
		{
			int recvbytes;
			recvbytes = recv(client_fd[n], buf, MAXDATASIZE, 0);
			if (recvbytes !=-1)
			{ 
				buf[recvbytes] = '\0'; 
				printf( "Received: %d,%s\n", n, buf);
				send(client_fd[n], buf, recvbytes, 0);
			}
		}
	}

	return 0x1001;
}
