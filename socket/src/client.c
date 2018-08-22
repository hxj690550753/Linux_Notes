#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT        4321
#define BUFFER_SIZE 1024
#define HOST_NAME   "localhost"
#define MSG         "hello"
int main(void)
{
    int sockfd,sendbytes;
    char buf[BUFFER_SIZE];
    struct hostent *host;
    struct sockaddr_in serv_addr;

    /*地址解析函数*/
    if ((host = gethostbyname(HOST_NAME)) == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
    memset(buf, 0, sizeof(buf));
    //sprintf(buf, "%s", MSG);
    /*创建 socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    /*设置 sockaddr_in 结构体中相关参数*/
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);
    /*调用 connect 函数主动发起对服务器端的连接*/
    if(connect(sockfd,(struct sockaddr *)&serv_addr,
               sizeof(struct sockaddr))== -1)
    {
        perror("connect");
        exit(1);
    }
    /*发送消息给服务器端*/
    int time = 2;
    while(1)
    {
        if ((sendbytes = send(sockfd, buf, strlen(buf), 0)) == -1)
        {
            perror("send");
            exit(1);
        }
        memset(buf, 0, sizeof(buf));
        scanf("%s",buf);
    }

    close(sockfd);
    exit(0);
}
