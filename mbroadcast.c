#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>  
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <errno.h>

extern int errno;

/*
*  create broadcast socket fd
*   
*/
int mbroadcast_create_fd()
{
    int fd;
    const int opt = 1;

    if (-1 == (fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("err : %s\n",strerror(errno));
        return -1;
    } 

    if (-1 == setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)))
    {
        printf("err : %s\n",strerror(errno));
        return -1;    
    }

    return fd;
}

int mbroadcast_send(int fd, int port, char *msg, int len)
{
	struct sockaddr_in addrto; 
	int ret = -1,nlen = sizeof(addrto);

    bzero(&addrto, sizeof(struct sockaddr_in));  
    addrto.sin_family = AF_INET;  
    addrto.sin_addr.s_addr = inet_addr("255.255.255.255"); 
    addrto.sin_port = htons(port);

    ret = sendto(fd, msg, len, 0, (struct sockaddr*)&addrto, nlen);  
    if (ret < 0)  
	{  
    	printf("err : %s\n",strerror(errno));
    	return ret;  
	}  

	return 0;
}

int mbroadcast_bind(int fd, int port)
{
    struct sockaddr_in addr;

    bzero(&addr, sizeof(struct sockaddr_in));  
    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    addr.sin_port = htons(port); 

    if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)   
    {     
        printf("err : %s\n",strerror(errno));  
        return -1;  
    } 

    return 0;     
}

/*
*   reciver need bind first
*
*/
int mbroadcast_reciver(int fd, char *buf, int buf_len)
{
	struct sockaddr_in reciver;
	int ret = -1;
	int len = sizeof(reciver);  

    bzero(&reciver, sizeof(struct sockaddr_in)); 
    while(1)  
    {  
        //从广播地址接受消息  
        ret = recvfrom(fd, buf, buf_len, 0, (struct sockaddr*)&reciver, (socklen_t*)&len);  
        if (ret <= 0)  
        {  
            printf("err : %s\n",strerror(errno));  
        }  
        else  
        {         
            printf("%s\n", buf);
            //fflush(stdout);       
        }  
  
        sleep(1);  
    } 

    return 0;
}
