#include "ser.h"
//#include "cli.h"
#include "foio.h"
#include "fconn.h"



int main()
{
	cout<<"main"<<endl;
	SockSer sockser("127.0.0.1",6501);
	int listenfd = sockser.GetSockfd();
	processpool<SockCli>* pool = processpool<SockCli>::create(listenfd);
	if(pool)
	{
		pool->run();
		//delete pool;
		//pool = NULL;
	}
	return 0;
}
