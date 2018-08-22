#include "semaphore.h"

/*
 * 信号量用于表示资源的数量，是进程直接互斥和同步访问的机制
 * 共享内存SHM是把一块毫无保护的内存裸露在进程面前，没有
 * 经过Linux内核的任何操作，读写效率非常高，但是由于没有
 * 任何保护措施，因此必须小心地使用，一般而言配合信号量、
 * 互斥锁一起使用，以免数据被践踏
 */
int shm_id;
int sem_id;

//信号回调函数
void rm_sxm(int sig)
{
	shmctl(shm_id,IPC_RMID,NULL);	//删除共享内存
	semctl(sem_id,0,IPC_RMID);		//删除共享信号量
	printf("rm shm and sem\n");
	exit(1);
}

int main(void)
{
	//强制结束J，然后下次运行的时候，由于信号量没有被释放
	//再次申请信号量会造成死锁，因此需要捕获Ctrl+C信号然后释放信号量
	//捕获Ctrl+C信号
	signal(SIGINT,rm_sxm);
	
	//获得键值key并创建SHM共享内存,然后映射内存到虚拟空间
	key_t SHM_key = ftok(PROJ_PATH,SHM_ID);
	shm_id = shmget(SHM_key,SHMSIZE,IPC_CREAT|0666);
	char *shm_addr = shmat(shm_id,NULL,0);
	memset(shm_addr,0,SHMSIZE);
	
	//获取键值key并创建SEM信号量
	key_t SEM_key = ftok(PROJ_PATH,SEM_ID);
	sem_id = semget(SEM_key,2,IPC_CREAT|IPC_EXCL|0666);
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
		sem_p(sem_id,SPACE);			//申请空间
		fgets(shm_addr,SHMSIZE,stdin);	//写入共享内存
		printf("\n[OK]\n");
		sem_v(sem_id,DATA);				//增加了数据
	}
	
	return 0;
}