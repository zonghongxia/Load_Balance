#include "fconn.h"
#include "foio.h"
//#include "processpool.h"

int SockCli::m_epollfd = -1;


SockCli::SockCli(){}
SockCli::~SockCli(){}

void SockCli::init(int epollfd,int sockfd,const sockaddr_in & client_addr,int serfd)
{
//	cout<<"enter init connfd="<<sockfd<<endl;
	m_epollfd = epollfd;
	m_sockfd = sockfd;
//	cout<<"init m_sockfd="<<m_sockfd<<endl;
	m_address = client_addr;
	sersockfd = serfd;
	cout<<"init later m_sockfd="<<m_sockfd<<endl;
}

void SockCli::process()
{
	cout<<"process m_sockfd="<<m_sockfd<<endl;
//	cout<<"enter process"<<endl;
	char recvbuff[1024] = {0};
	while(1)
	{
		char buff[128] = {0};
		int ret = recv(m_sockfd,buff,127,0);
		if(ret < 0)
		{
			if((errno == EAGAIN) || (errno == EWOULDBLOCK))
			{
				cout<<"read later"<<endl;
				cout<<"recvbuf="<<recvbuff<<endl;
				send(sersockfd,recvbuff,strlen(recvbuff),0);
				memset(recvbuff,0,sizeof(recvbuff));
				int re = recv(sersockfd,recvbuff,127,0);
				if(re < 0)
				{
					//;
				}
				cout<<"ser huifu="<<recvbuff<<endl;
				send(m_sockfd,recvbuff,sizeof(recvbuff),0);
				cout<<endl;
				break;
			}
			perror("mistake:=");
			close(m_sockfd);
			break;
		}
		else if(ret == 0)
		{
			close(m_sockfd);
			removefd(m_epollfd,m_sockfd);
		}
		else
		{
			strcat(recvbuff,buff);
			memset(buff,0,sizeof(buff));
		}
	}


#if 0
	char recvbuf[128] = {0};
	int idx = 0;
	int ret = -1;
	while(true)
	{
		char buf[128] = {0};
		cout<<"wait accept foio recv"<<endl;
		ret = recv(m_sockfd,buf,127,0);
		cout<<"recv size ret="<<ret<<endl;
		cout<<"recv over size:"<<strlen(buf)<<endl;
		if(strncmp(buf,"#@$",3) == 0)
		{
			buf[13] = '1';
			send(m_sockfd,buf,sizeof(buf),0);
			break;
		}
		//cout<<"buf="<<buf<<endl;
		if(ret < 0 && errno == EAGAIN)
		{
			/*if(errno != EAGAIN)
			{
				cout<<"enter errno"<<endl;
				continue;
				//removefd(m_epollfd,m_sockfd);
			}
			else if(ret == -1)
			{
				break;
			}
			else
			{*/
				break;
			//}
			/*
			send(sersockfd,recvbuf,sizeof(recvbuf)-1,0);

			cout<<"recvbuf:"<<recvbuf<<endl;
			memset(recvbuf,0,sizeof(recvbuf));
			int re = recv(sersockfd,recvbuf,127,0);
			if(re < 0)
			{
				//send(m_sockfd,recvbuf,sizeof(recvbuf),0);
			}
			send(m_sockfd,recvbuf,sizeof(recvbuf),0);
			memset(recvbuf,0,sizeof(recvbuf));
			cout<<endl;*/
			//continue;
		}
		else if(ret == 0)
		{
			removefd(m_epollfd,m_sockfd);
			break;
		}
		else
		{
			/*cout<<buf<<endl;
			strcpy(recvbuf,buf);*/

			send(sersockfd,buf,strlen(buf),0);

			cout<<"buff="<<buf<<endl;
			int re = recv(sersockfd,recvbuf,127,0);
			if(re < 0)
			{
				//send(m_sockfd,recvbuf,sizeof(recvbuf),0);
			}
			cout<<"recvbuff="<<recvbuf<<endl;
			send(m_sockfd,recvbuf,sizeof(recvbuf),0);
			memset(recvbuf,0,sizeof(recvbuf));
			cout<<endl;
			break;
		}
	}
#endif
}



