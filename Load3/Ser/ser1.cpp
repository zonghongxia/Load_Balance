#include"ser.h"
#include "processpool.h"
#include "conn.h"
int main()
{
	SockSer fdsock("127.0.0.1",9521);
	int listenfd = fdsock.GetSockfd();
	processpool<SockCli>* pool = processpool<SockCli>::create(listenfd);
	if(pool)
	{
		pool->run();
		delete pool;
		pool = NULL;
	}

	return 0;
}
