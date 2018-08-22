#include "semaphore.h"

/*
 * 信号量用于表示资源的数量，是进程直接互斥和同步访问的机制
 * 共享内存SHM是把一块毫无保护的内存裸露在进程面前，没有
 * 经过Linux内核的任何操作，读写效率非常高，但是由于没有
 * 任何保护措施，因此必须小心地使用，一般而言配合信号量、
 * 互斥锁一起使用，以免数据被践踏
 */


int main(void)
{
	//获得键值key并创建SHM共享内存,然后映射内存到虚拟空间
	key_t SHM_key = ftok(PROJ_PATH,SHM_ID);
	int shm_id = shmget(SHM_key,SHMSIZE,IPC_CREAT|0666);
	char *shm_addr = shmat(shm_id,NULL,0);
	
	//获取键值key并创建SEM信号量
	key_t SEM_key = ftok(PROJ_PATH,SEM_ID);
	int sem_id = semget(SEM_key,2,IPC_CREAT|IPC_EXCL|0666);
	if(sem_id == -1 && errno == EEXIST)
	{
		sem_id = semget(SEM_key,2,0666);
	}
	else
	{
		seminit(sem_id,DATA,0);		//第0个元素初始化为0，代表数据
		seminit(sem_id,SPACE,1);	//第1个元素初始化为1，代表空间
	}
	
	while(1)
	{
		sem_p(sem_id,DATA);				//申请数据
		if(errno == EIDRM)				//如果信号量被释放，退出函数
			break;
		printf("from J:%s",shm_addr);	//写入共享内存
		sem_v(sem_id,SPACE);			//增加了空间
		if(errno == EIDRM)				//如果信号量被释放，退出函数
			break;
	}
	
	return 0;
}