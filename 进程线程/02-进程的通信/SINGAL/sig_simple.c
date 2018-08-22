#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * 信号的通讯是异步的，它会使得原本某个进程的动作被打断
 * 因此如果进程不希望当前动作被打断，可以使用阻塞掩码对
 * 信号进行阻塞，待当前动作完成后再进行响应。或者使用了
 * Linux内核提供的一些信号安全函数，Linux保证执行这些函
 * 数不会被信号的到来而打断
 */

void handler(int sig)
{
	printf("catched a signal:%d\n",sig);
}

int main(void)
{
	signal(SIGHUP,handler);		//终端被关闭
	signal(SIGINT,handler);		//键盘中断
	signal(SIGQUIT,handler);	//键盘退出
	
	printf("waitting for some signal...\n");
	pause();					//进程挂起
	return 0;
}