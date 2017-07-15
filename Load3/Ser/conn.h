//#ifndef CONN_H
//#define CONN_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <error.h>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

//#include "processpool.h"

using namespace std;

typedef struct sockaddr_in sockaddr_in;

#define MAXLISTEN 5

class SockCli
{
	static int m_epollfd;
	int m_sockfd;
	sockaddr_in m_address;
public:
	SockCli();
	void init(int epollfd,int sockfd,const sockaddr_in& client_addr);
	void process();
	~SockCli();
};

//#endif
