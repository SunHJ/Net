#ifndef __NET_PUBLIC_H__
#define __NET_PUBLIC_H__

enum KAsyncSocketEventType
{
	ASYNC_SOCKET_EVENT_INVALID	= 0,	//invalid event
	ASYNC_SOCKET_EVENT_ACCEPT	= 1,	//socket accept
	ASYNC_SOCKET_EVENT_CONNECT	= 2,	//socket connect
	ASYNC_SOCKET_EVENT_IN		= 3,	//socket read available
	ASYNC_SOCKET_EVENT_OUT		= 4		//socket write available
};

#define MAX_WAIT_ACCEPT_EVENT	32
#define MAX_SOCKET_EVENT		(1024 + MAX_WAIT_ACCEPT_EVENT)

#endif