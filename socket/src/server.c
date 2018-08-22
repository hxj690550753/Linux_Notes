#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 4321
#define BUFFER_SIZE 1024
#define MAX_QUE_CONN_NM 5

int main()
{
    struct sockaddr_in server_sockaddr,client_sockaddr;
    int sin_size,recvbytes;
    int sockfd, client_fd,fd;
    char buf[BUFFER_SIZE];
    fd_set inset;

    /*建立 socket 连接*/
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
    {
        perror("socket");
        exit(1);
    }
    printf("Socket id = %d\n",sockfd);
    /*设置 sockaddr_in 结构体中相关参数*/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);
    int i = 1;/* 允许重复使用本地地址与套接字进行绑定 */
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    /*绑定函数 bind()*/
    if (bind(sockfd, (struct sockaddr *)&server_sockaddr,
             sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    printf("Bind success!\n");
    /*调用 listen()函数，创建未处理请求的队列*/
    if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Listening....\n");
    /*调用 accept()函数，等待客户端的连接*/
    if ((client_fd = accept(sockfd,
                            (struct sockaddr *)&client_sockaddr, &sin_size)) == -1)
    {
        perror("accept");
        exit(1);
    }/*调用 recv()函数接收客户端的请求*/
    memset(buf, 0, sizeof(buf));

    FD_ZERO(&inset);
    FD_SET(client_fd, &inset);

    while(1)
    {
        if ((recvbytes = recv(client_fd, buf, BUFFER_SIZE, 0)) > 0)
        {
            printf("%d-",recvbytes);
            perror("recv>0");
            printf("Received a message: %s\n", buf);
            memset(buf, 0, sizeof(buf));
        }
        else
        {
            printf("%d-",recvbytes);
            perror("recv<0");
            close(fd);
            close(sockfd);
            printf("Client %d(socket) has left\n", fd);
            break;
        }
    }
#ifdef DEBUG
    while(1)
    {
        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &inset) > 0)
            {
                if(fd == client_fd)
                {
                    if ((recvbytes = recv(client_fd, buf, BUFFER_SIZE, 0)) > 0)
                    {
                        perror("recv>0");
                        printf("Received a message: %s\n", buf);
                        FD_ZERO(&inset);
                        FD_SET(client_fd, &inset);
                        memset(buf, 0, sizeof(buf));
                    }
                    else
                    {
                        perror("recv<0");
                        close(fd);
                        close(sockfd);
                        FD_CLR(fd, &inset);
                        printf("Client %d(socket) has left\n", fd);
                        exit(0);
                    }
                }
            }
        }
    }
#endif
    close(sockfd);
    exit(0);
}
