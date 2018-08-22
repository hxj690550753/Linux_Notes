#include "POSIX_u_name.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

/*
 * 编译的时候需要加上-pthread选项
 * 无名信号量主要用于同一个进程的线程之间的同步互斥
 */

sem_t *p_sem = NULL;
char *shm_addr = NULL;
 
/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine(void *arg)
{
	//输出参数
	char *s = (char*)arg;
	printf("arg:%s\n",s);
	
	while(1)
	{
		sem_wait(p_sem);
		printf("from main:%s\n",shm_addr);
		if(!strncmp(shm_addr,"quit",4))
			break;
	}
	
	//结束线程
	sleep(1);
	pthread_exit(NULL);
}

int main(void)
{
	//初始化信号量
	p_sem = (sem_t *)malloc(sizeof(sem_t));
	sem_init(p_sem,0,0);	//使用前初始化
	if(p_sem == NULL)
	{
		perror("sem_init");
		return -1;
	}
	
	//创建或打开共享内存
	key_t key = ftok(PROJ_PATH,PROJ_ID);
	int shm_id = shmget(key,POSIX_SHMSIZE,IPC_CREAT|0666);
	shm_addr = shmat(shm_id,NULL,0);

	//设置属性，可分离的
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	//用该属性创建线程，指定例程和传入参数
	pthread_t tid;
	pthread_create(&tid,&attr,routine,(void*)"main");
	
	//使用无名信号量通讯
	while(1)
	{
		fgets(shm_addr,POSIX_SHMSIZE,stdin);
		sem_post(p_sem);
		
		if(!strncmp(shm_addr,"quit",4))
			break;
	}
	
	//关闭
	free(p_sem);
	munmap(shm_addr,POSIX_SHMSIZE);
	
	return 0;
}