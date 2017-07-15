#ifndef SER_H
#define SER_H

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
#include <string.h>

//#include "processpool.h"

using namespace std;

typedef struct sockaddr_in sockaddr_in;

#define MAXLISTEN 5

class SockSer
{
private:
	int sockfd;
	int port;
	char *Ipbuf;
	//static map<int,sockadd_in> Map;
	void Bind();
	void Listen();
public:
	SockSer(char *buf,int po);
	int GetSockfd();
	~SockSer();
};

#endif
