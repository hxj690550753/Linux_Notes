#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * 条件变量用于共享资源具有数量概念的同步互斥访问
 * 主要是pthread_cond_wait()函数，会自动把原本持有的锁解锁，
 * 然后等待唤醒，唤醒后会自动重新加锁，防止等待队列中死锁出现
 */


int balance =  0;		//共享资源，余额开始为0

pthread_mutex_t mutex;	//互斥锁
pthread_cond_t cond;	//条件变量

/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine(void *arg)
{
	//输出参数
	int *msg = (int*)arg;
	printf("pthread arg:%d\n",*msg);
	
	//加锁，取钱
	pthread_mutex_lock(&mutex);
	//余额不足，进入等待队列，在队列中会自动解锁，当唤醒的时候会自动加锁
	while(balance < 100)				
		pthread_cond_wait(&cond,&mutex);
	//取走100
	balance -=100;						
	printf("pthread get 100 and balance:%d\n",balance);
	//解锁
	pthread_mutex_unlock(&mutex);
	//结束线程
	pthread_exit(NULL);
}


int main(void)
{
	//初始化锁
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	
	//设置属性，可分离的
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//用该属性创建线程，指定例程和传入参数
	pthread_t tid;
	int i = 0;
	for(i = 0; i<10; i++)
		pthread_create(&tid,&attr,routine,(void*)&i);
	
	//加锁，打钱
	pthread_mutex_lock(&mutex);
	balance += (i*100);
	printf("main fill balance:%d\n",balance);
	//通知所有等待的线程
	pthread_cond_broadcast(&cond);
	//解锁
	pthread_mutex_unlock(&mutex);
	
	//阻塞自身，否则进程结束，线程也相应结束
	char c;
	scanf("%c",&c);
	
	//摧毁锁
	pthread_mutex_destroy(&mutex);
}
