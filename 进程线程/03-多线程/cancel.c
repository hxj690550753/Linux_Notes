#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* 
 * 演示了一个默认属性的线程执行过程，当线程结束的时候进程复制回收资源
 * 同时进程主动请求取消线程，线程正确响应这个请求
 */

//互斥锁
pthread_mutex_t m;


void handler(void *arg)
{
	pthread_mutex_unlock(&m);
	printf("pthread unlock in handler()\n");
}

/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine(void *arg)
{
	//加锁前，把handler压入栈，以免中途退出
	pthread_cleanup_push(handler,NULL);
	pthread_mutex_lock(&m);
	printf("pthread lock\n");
	
	//输出参数
	char *s = (char*)arg;
	printf("arg:%s\n",s);
	
	//睡眠，如果有取消信号，handler被执行
	sleep(10);
	
	//解锁后，弹出handler栈
	pthread_cleanup_pop(0);
	
	//结束线程
	pthread_exit("pthread exit");
}

int main(void)
{
	//初始化互斥锁
	pthread_mutex_init(&m,NULL);

	//默认属性创建线程，指定例程和传入参数
	pthread_t tid;
	pthread_create(&tid,NULL,routine,(void*)"main");
	
	//等待1s后发送一个去取消请求，释放线程
	pthread_cancel(tid);
	
	//主进程可以加锁，因为线程退出后执行handler进行解锁
	pthread_mutex_lock(&m);
	printf("main lock!\n");
	pthread_mutex_unlock(&m);
	printf("main unlock!\n");
	
	return 0;
}










