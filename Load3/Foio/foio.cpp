#include "foio.h"

//map<int,sockaddr_in> SockCli::TableConnfd = map<int,sockaddr_in>();


/*void InsertSerIp()
{
	FSer ser1("127.0.0.1",9510);	
	FSer ser2("127.0.0.1",9511);	
	FSer ser3("127.0.0.1",9512);
	TableSer.push_back(ser1);
	TableSer.push_back(ser2);
	TableSer.push_back(ser3);
}*/


FCli::FCli(const char *buf,int po):port(po)
{
	strcpy(strptr,buf);
	//sockfd = socket(AF_INET,SOCK_STREAM,0);
	//assert(sockfd >= 0);
	//Connect();
}

void FCli::CreateCli()
{
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd >= 0);
	Connect();
}

void FCli::Connect()
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


int FCli::GetSockfd()
{
	return sockfd;
}


FCli::~FCli()
{
	close(sockfd);
}


FSer::FSer(char *buf,int po)
{
	memset(Ip,0,sizeof(Ip));
	strncpy(Ip,buf,strlen(buf));
	port = po;
}
FSer::FSer(const FSer &ser)
{
	strcpy(Ip,ser.Ip);
	port = ser.port;
}
FSer::~FSer(){}
void FSer::init(char *buf,int po)
{
	int len = strlen(buf);
	strncpy(Ip,buf,len);
	port = po;
}

char* FSer::GetIp()
{
	return Ip;
}

int FSer::GetPort()
{
	return port;
}
