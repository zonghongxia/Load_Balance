#include "cli.h"

SockCli::SockCli(const char *buf,int po=6510,int Htag):port(po),Heart_tag(Htag)
{
	strcpy(strptr,buf);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd >= 0);
	Connect();
	Create_pthread();
}

void SockCli::Connect()
{
	char buf[128] = {0};
	strncpy(buf,strptr,strlen(strptr));
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(buf);

	int ret = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(ret >= 0);
}

void SockCli::Heart_Bag()
{
	cout<<"enter Heart_Bag"<<endl;
	send(sockfd,"#@$keepalive=0",14,0);
	char Heartbuf[128] = {0};
	int n = recv(sockfd,Heartbuf,127,0);
	if(n <= 0)
	{
		m_lock_Heart.unlock();
		close(sockfd);
	}
	cout<<"Heart_Bag = "<<Heartbuf<<endl;
	m_lock_Heart.unlock();
}


void  SockCli::another()
{
	cout<<"enter another"<<endl;
	while(1)
	{
		cout<<"sleep front"<<endl;
		sleep(10);
		cout<<"sleep behind"<<endl;
		while(!m_lock_Heart.lock())
		{
			;
		}
		if(Heart_tag == 1)
		{
			Heart_tag = 0;
			m_lock_Heart.unlock();
		}
		else
		{
			Heart_Bag();
		}
	}
}

void* SockCli::worker(void *arg)
{
	cout<<"enter worker"<<endl;
	SockCli *cli = (SockCli*)arg;
	cli->another();
	return cli;
}

void SockCli::Create_pthread()
{
	pthread_t id;
	int res = pthread_create(&id,NULL,worker,this);
	if(res != 0)
	{
		perror("pthread_create faile!!");
	}
	else
	{
		cout<<"pthread success!!"<<endl;
	}
}

BOOL SockCli::Recv()
{
	char recvbuff[1024] = {0};
	int n = recv(sockfd,recvbuff,1023,0);
	if(n <= 0)
	{
		close(sockfd);
		return false;
	}
	printf("%s\n",recvbuff);
	m_lock_Heart.unlock();
	return true;
}

SendTag SockCli::Send()
{
	SendTag tf;
	printf("input:\n");
	char buff[1024] = {0};
	fgets(buff,1023,stdin);
	while(!m_lock_Heart.lock())
	{
		;
	}
	if(strncmp(buff,"end",3) == 0)
	{
		tf.Tag = false;
	}
	if(strncmp(buff,"\n",2) == 0)
	{
		tf.tag = 1;
		tf.Tag = false;
	}
	else
	{
		tf.Tag = true;
		send(sockfd,buff,strlen(buff),0);
	}
	return tf;
}
BOOL SockCli::SendSer(char *buff)
{
	send(sockfd,buff,strlen(buff),0);
	return true;
}
SockCli::~SockCli()
{
	close(sockfd);
}
