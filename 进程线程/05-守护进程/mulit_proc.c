#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
    pid_t child1;
    pid_t child2;
    pid_t child;
    int status1;
    int status2;

    //创建子进程1
    child1 = fork();

    //子进程1处理
    if(child1 < 0)                     //出错处理
    {
        perror("[FALSE] fork() child1");
        exit(1);
    }
    else if(child1 == 0)                //子进程1创建成功
    {
        printf("[OK] child1 execlp()\n");
        execlp("ls","ls","-l",NULL);
        exit(0);
    }
    else
    {
        //创建子进程2
        child2 = fork();
        //子进程2处理
        if(child2 < 0)                     //出错处理
        {
            perror("[FALSE] fork() child2");
            exit(1);
        }
        else if(child2 == 0)                //子进程2创建成功
        {
            printf("[OK] child2 sleep()\n");
            sleep(5);
            exit(0);
        }

        //父进程处理
        //阻塞等待子进程1
        child = waitpid(child1,&status1,0);
        if(child == child1)
        {
            printf("[OK] child1 is end with value:%d\n",status1);
        }
        while(1)
        {
            //非阻塞等待子进程2结束
            child = waitpid(child2,&status2,WNOHANG);
            if(child == child2)
            {
                printf("[OK] child2 is end with value:%d\n",status2);
                break;
            }
            else
            {
                printf("[OK] child2 is not end\n");
                sleep(1);
            }
        }
    }


    return 0;
}

