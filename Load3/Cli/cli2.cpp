#include "cli.h"

int main()
{
	SockCli fdsock("127.0.0.1",6501);
	while(1)
	{
		SendTag tf = fdsock.Send();
		if(tf.Tag)
		{
			fdsock.Recv();
		}
		else if(tf.tag == 1)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	return 0;
}
