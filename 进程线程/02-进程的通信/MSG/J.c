#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* 
 * 消息队列的通讯非常简便，内核为其进行内存分配、检查边界
 * 、设置阻塞以及各种权限监控，因此消息队列的通讯效率不高
 * 不适合海量的数据通讯，只适用于一些进程直接普通的需要数
 * 据识别的通讯
 */


int main(void)
{
	//获取键值
	key_t key = ftok(PROJ_PATH,PROJ_ID);
	//创建或者获取消息队列ID
	int msg_id = msgget(key,IPC_CREAT|0666);
	
	struct msg_buf msg;
	msg.type = J2R;			//标识消息
	strncpy(msg.content,"I'm J,nice to meet you!\n",MSGSIZE);
	
	//发送信息
	if(msgsnd(msg_id,&msg,strlen(msg.content),0) != 0)
	{
		perror("msgsend()");
		exit(1);
	}
	else
		printf("J send the msg:%s with type:%ld\n",msg.content,msg.type);
	
}
