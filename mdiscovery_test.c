#include <stdio.h>
#include <string.h>
#include "mdiscovery.h"

int main(int argc, char ** args)
{
	int fd;

	//setvbuf(stdout, NULL, _IONBF, 0);   
    //fflush(stdout);   
	if (0 > (fd = mbroadcast_create_fd()))
	{
		printf("failed when create fd\n");
		return -1;
	}

	if (argc == 2)
	{
		while(1)
		{
			mbroadcast_send(fd, 6000, args[1], strlen(args[1]));
		}	
	}
	else
	{
		char buf[512];

		mbroadcast_bind(fd, 6000);
		mbroadcast_reciver(fd, buf, sizeof buf);	
	}

	return 0;
}
