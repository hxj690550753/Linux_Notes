#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* 
 * 演示了一个可分离属性的多线程执行过程，当线程结束的时候就会自动释放资源
 * 不需要进程复制回收资源
 */


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
	
	//结束线程
	sleep(1);
	pthread_exit(NULL);
}

int main(void)
{
	//设置属性，可分离的
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	//用该属性创建线程，指定例程和传入参数
	pthread_t tid;
	pthread_create(&tid,&attr,routine,(void*)"main");
	
	//阻塞自身，否则进程结束，线程也相应结束
	pause();
	return 0;
}










