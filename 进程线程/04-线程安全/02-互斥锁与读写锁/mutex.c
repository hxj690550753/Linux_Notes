#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * 互斥锁主要用于对一种没有操作类型的资源或者非常重要的资源加锁
 * 因为它不对资源加以区分，只有“上锁”和“解锁”功能，一旦上锁，一定
 * 要等到解锁后才能再次被访问，着对于频繁读的资源而言效率非常低
 */ 

pthread_mutex_t m;		//互斥锁


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
	
	pthread_mutex_lock(&m);
	printf("pthread say:A\n");
	pthread_mutex_unlock(&m);
	
	//结束线程
	sleep(1);
	pthread_exit(NULL);
}


int main(void)
{
	//初始化锁
	pthread_mutex_init(&m,NULL);
	
	//设置属性，可分离的
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//用该属性创建线程，指定例程和传入参数
	pthread_t tid;
	pthread_create(&tid,&attr,routine,(void*)"main");
	
	//加锁访问
	pthread_mutex_lock(&m);
	printf("main say:B\n");
	pthread_mutex_unlock(&m);
	
	//阻塞自身，否则进程结束，线程也相应结束
	pause();
	
	//摧毁锁
	pthread_mutex_destroy(&m);
}






