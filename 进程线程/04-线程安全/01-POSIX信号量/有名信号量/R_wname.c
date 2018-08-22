#include "POSIX_w_name.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

/*
 * 编译的时候需要加上-pthread选项
 * 有名信号量主要用于不同进程的线程之间的同步互斥
 * 使用POSIX信号量，比起system-V的信号量而言，使用上非常简洁
 */


int main(void)
{
	//创建或打开共享内存
	key_t key = ftok(PROJ_PATH,PROJ_ID);
	int shm_id = shmget(key,POSIX_SHMSIZE,IPC_CREAT|0666);
	char *shm_addr = shmat(shm_id,NULL,0);

	//创建或打开有名信号量
	sem_t *p_sem;
	p_sem = sem_open(POSIX_SEMNAME,O_CREAT,0777,0);
	
	//使用信号量同步共享内存读
	while(1)
	{
		sem_wait(p_sem);
		printf("from J:%s",shm_addr);
		if(!strncmp(shm_addr,"quit",4))
			break;
	}
	
	sem_close(p_sem);
	return 0;
}