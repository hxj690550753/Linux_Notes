#include "share_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
 * 共享内存SHM是把一块毫无保护的内存裸露在进程面前，没有
 * 经过Linux内核的任何操作，读写效率非常高，但是由于没有
 * 任何保护措施，因此必须小心地使用，一般而言配合信号量、
 * 互斥锁一起使用，以免数据被践踏
 */

int main(void)
{
	//获得键值key
	key_t key = ftok(PROJ_PATH,PROJ_ID);
	
	//用key创建共享内存并获得ID
	int shm_id = shmget(key,SHMSIZE,IPC_CREAT|0666);
	
	//把共享内存映射到本进程的虚拟地址
	char *p = shmat(shm_id,NULL,0);
	pid_t other_pid = (*(pid_t*)p);
	printf("from pid:%d SHM:%s",(int)other_pid,p+sizeof(pid_t));
	
	kill(other_pid,SIGINT);
	//释放共享内存指针引用
	shmdt(p);
	
	
	return 0;
}