#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>


/*
 * 信号量用于表示资源的数量，是进程直接互斥和同步访问的机制
 * 共享内存SHM是把一块毫无保护的内存裸露在进程面前，没有
 * 经过Linux内核的任何操作，读写效率非常高，但是由于没有
 * 任何保护措施，因此必须小心地使用，一般而言配合信号量、
 * 互斥锁一起使用，以免数据被践踏
 */

#define SHMSIZE		1024

#define PROJ_PATH	"."
#define SHM_ID		1
#define SEM_ID		2

#define DATA		0
#define SPACE		1

//信号量操作联合体
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};


/**
  * @brief	信号量的p操作，用于"申请资源"，资源会变少1
  * @param	semid：	信号量的ID
  * @param	semnum：信号量数组的下标
  * @retval	None
  */
static void sem_p(int semid, int semnum)
{
	struct sembuf op[1];
	op[0].sem_num = semnum;
	op[0].sem_op = -1;
	op[0].sem_flg = 0;
	
	semop(semid,op,1);
}

/**
  * @brief	信号量的v操作，用于"释放资源"，资源会增加1
  * @param	semid：	信号量的ID
  * @param	semnum：信号量数组的下标
  * @retval	None
  */
static void sem_v(int semid, int semnum)
{
	struct sembuf op[1];
	op[0].sem_num = semnum;
	op[0].sem_op = 1;
	op[0].sem_flg = 0;
	
	semop(semid,op,1);
}

/**
  * @brief	初始化一个信号量，用指定的val填充信号量操作结构体
  *			并赋值给num的信号量
  * @param	semid：	信号量的ID
  * @param	semnum：待赋值的信号量下标
  * @param	val:	需要指定的数值
  * @retval	None
  */
static void seminit(int semid, int semnum,int val)
{
	union semun s;
	s.val = val;
	semctl(semid,semnum,SETVAL,s);		//设置num对应信号量的值
}


#endif

