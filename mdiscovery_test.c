#include <stdio.h>
#include <string.h>
#include "mdiscovery.h"
#include "multicast.h"

int main(int argc, char ** args)
{
	/*int fd;
 
	if (0 > (fd = mbroadcast_create_fd()))
	{
		printf("failed when create fd\n");
		return -1;
	}*/

	if (argc == 2)
	{
	    int i;
		for (i = 0; i < 10; i++)
		{
			//mbroadcast_send(fd, 6000, args[1], strlen(args[1]));
		    multicast_client();
		}	
	}
	else
	{
		/*char buf[512];

		mbroadcast_bind(fd, 6000);
		mbroadcast_reciver(fd, buf, sizeof buf);*/
		multicast_server_init();	
	}

	return 0;
}
