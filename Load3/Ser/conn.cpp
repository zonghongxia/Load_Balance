#include "conn.h"
#include "processpool.h"

int SockCli::m_epollfd = -1;


SockCli::SockCli(){}
SockCli::~SockCli(){}

void SockCli::init(int epollfd,int sockfd,const sockaddr_in & client_addr)
{
	m_epollfd = epollfd;
	m_sockfd = sockfd;
	m_address = client_addr;
}

void SockCli::process()
{
	int idx = 0;
	int ret = -1;
	while(true)
	{
		char buf[128] = {0};
		ret = recv(m_sockfd,buf,127,0);
		if(ret < 0)
		{
			if(errno != EAGAIN)
			{
				removefd(m_epollfd,m_sockfd);
			}
			send(m_sockfd,"ok",2,0);
			break;
		}
		else if(ret == 0)
		{
			removefd(m_epollfd,m_sockfd);
			break;
		}
		else
		{
			cout<<buf<<endl;
		}
	}
}



