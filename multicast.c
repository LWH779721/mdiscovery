#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string.h>
#include <errno.h>
#include <unistd.h> 
#include <stdlib.h>
#include "mlanguage.h"
#include "mlog.h"

extern int errno;

int multicast_server_init()
{
    int fd;
    const int opt = 1;
    struct sockaddr_in localSock;
    struct ip_mreq group;
    int datalen = 1500;
    char databuf[1500];

    if (-1 == (fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("err : %s\n",strerror(errno));
        return -1;
    } 

    if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)))
    {
        printf("err : %s\n",strerror(errno));
        close(fd);
        return -1;    
    }
    
    memset((char *) &localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(49500);
    localSock.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr*)&localSock, sizeof(localSock)))
    {
        perror("Binding datagram socket error");
        close(fd);
        return -1;
    } 
    
    group.imr_multiaddr.s_addr = inet_addr("227.0.0.25");
    group.imr_interface.s_addr = htonl(INADDR_ANY);
    if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
    {
        perror("Adding multicast group error");
        close(fd);
        return -1;
    }
    
    struct sockaddr_in reciver;
	int ret;
	int len = sizeof(reciver);  

    bzero(&reciver, sizeof(struct sockaddr_in)); 
    while(1)  
    {  
        //从广播地址接受消息  
        ret = recvfrom(fd, databuf, datalen, 0, (struct sockaddr*)&reciver, (socklen_t*)&len);  
        if (ret <= 0)  
        {  
            printf("err : %s\n",strerror(errno));  
        }  
        else  
        {   
            databuf[ret] = 0;      
            printf("%s\n", databuf);     
        }  
  
        sleep(1);  
    } 
    
    return 0;
}

int multicast_client()
{
    struct in_addr localInterface;
    struct sockaddr_in groupSock;
    int sd;
    char databuf[1024] = "Multicast test message lol!";
    int datalen = sizeof(databuf);
        
    sd = socket(AF_INET, SOCK_DGRAM, 0);
     if(sd < 0) {
          perror("Opening datagram socket error");
          exit(1);
     } else
          printf("Opening the datagram socket...OK.\n");
    
     memset((char *) &groupSock, 0, sizeof(groupSock));
     groupSock.sin_family = AF_INET;
     groupSock.sin_addr.s_addr = inet_addr("227.0.0.25");
     groupSock.sin_port = htons(49500);


     localInterface.s_addr = htonl(INADDR_ANY);
     if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0) {
        perror("Setting local interface error");
        exit(1);
     } else
        printf("Setting the local interface...OK\n");


    if (sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) >= 0) 
    {
        printf("Sending datagram message...OK\n");
    }
    
    return 0;
}
