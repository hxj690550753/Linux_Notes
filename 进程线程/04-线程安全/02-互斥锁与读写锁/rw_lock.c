#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * 为了解决互斥锁对资源不加以区别的缺点，于是有读写锁，对于一些
 * 强烈分别读写的资源而言，读的操作应该是可以并发的，但是不能被
 * 写，而写的操作应该是阻塞的，不能被任何的读写
 */

static pthread_rwlock_t rwlock;
int global = 0;

/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  *			写全局变量
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine1(void *arg)
{
	//输出参数
	char *s = (char*)arg;
	printf("pthread 1 arg:%s\n",s);
	
	//加写锁
	pthread_rwlock_wrlock(&rwlock);
	global += 1;
	printf("pthread 2 say:%d\n",global);
	pthread_rwlock_unlock(&rwlock);
	
	//结束线程
	pthread_exit(NULL);
}

/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  *			写全局变量
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine2(void *arg)
{
	//输出参数
	char *s = (char*)arg;
	printf("pthread 2 arg:%s\n",s);
	
	//加写锁
	pthread_rwlock_wrlock(&rwlock);
	global += 1;
	printf("pthread 2 say:%d\n",global);
	pthread_rwlock_unlock(&rwlock);
	
	//结束线程
	pthread_exit(NULL);
}

/**
  * @brief	线程的执行例程，当线程被创建的时候，可以指定执行例程
  *			读全局变量
  * @param	arg：参数指针
  * @retval	返回void*指针
  */
void *routine3(void *arg)
{
	//输出参数
	char *s = (char*)arg;
	printf("pthread 3 arg:%s\n",s);
	
	//加读锁
	pthread_rwlock_rdlock(&rwlock);
	printf("pthread 3 say:%d\n",global);
	pthread_rwlock_unlock(&rwlock);
	
	//结束线程
	pthread_exit(NULL);
}

int main(void)
{
	//初始化读写锁
	pthread_rwlock_init(&rwlock,NULL);
	
	//设置属性，可分离的
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	////三条线程，用该属性创建线程，指定例程和传入参数
	pthread_t t1,t2,t3;
	pthread_create(&t2,&attr,routine2,(void*)"main2");
	pthread_create(&t1,&attr,routine1,(void*)"main1");
	pthread_create(&t3,&attr,routine3,(void*)"main3");
	
	
	//阻塞自身，否则进程结束，线程也相应结束
	char pause;
	scanf("%c",&pause);
	
	//摧毁
	pthread_rwlock_destroy(&rwlock);
	return 0;
}