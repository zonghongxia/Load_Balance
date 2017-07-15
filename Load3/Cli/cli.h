#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <string.h>
#include <iostream>
#include "locker.h"

using namespace std;

typedef void* Pthread;

#define MAXLISTEN 5
typedef bool BOOL;

typedef struct SendTag
{
	int tag;
	bool Tag;
}SendTag;

class SockCli
{
private:
    int sockfd;
    char strptr[128];
	int port;
	int Heart_tag;
	locker m_lock_Heart;
	void Connect();
public:
    SockCli(const char *buff,int port,int Htag=0);
	void Create_pthread();
	void  another();
	static void* worker(void *arg);
	void Heart_Bag();
	BOOL Recv();
	SendTag Send();
	BOOL SendSer(char *buf);
	~SockCli();
};
