#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
    pid_t pid;
    int i,fd;
    char *buf = "This is a Daemon!\n";

    //第1步，创建子进程，父进程退出
    pid = fork();
    if(pid < 0)
    {
        perror("[FALSE] fork()");
        exit(1);
    }
    else if(pid > 0)
    {
        exit(0);
    }

    //第2步，创建新会话
    setsid();
    //第3步，转换当前目录为根目录
    chdir("/");
    //第4步，重设文件掩码
    umask(0);
    //第5步，关闭文件描述符
    for(i = 0; i<getdtablesize(); i++)
    {
        close(i);
    }

    //子进程开始正式工作
    while(1)
    {
        if((fd = open("/tmp/daemon.log",
                      O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
        {
            perror("[FLASE] open()");
            exit(1);
        }
        write(fd,buf,strlen(buf)+1);
        close(fd);
        sleep(5);
    }
}

