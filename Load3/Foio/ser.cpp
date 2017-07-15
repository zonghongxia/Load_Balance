#include "ser.h"
//#include "processpool.h"

SockSer::SockSer(char *buf,int po)
{
	port = po;
	Ipbuf = new char[strlen(buf)+1];
	strcpy(Ipbuf,buf);
	Ipbuf[strlen(buf)] = '\0';
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd >= 0);
	Bind();
	Listen();
}

void SockSer::Bind()
{
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(Ipbuf);

	int ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(ret != -1);
}
void SockSer::Listen()
{
	int ret = listen(sockfd,MAXLISTEN);
	assert(ret != -1);
}

int SockSer::GetSockfd()
{
	return sockfd;
}

SockSer::~SockSer()
{
	delete [] Ipbuf;
	close(sockfd);
}


