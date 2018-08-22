#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* 
 * 演示了一个默认属性的多线程执行过程，由于默认属性中是“结合的”
 * 因此线程结束后会变成“僵尸线程”，等待进程回收资源并释放资源，
 * 可以设置属性“分离的”，当线程结束的时候就会自动释放资源
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
	pthread_exit("pthread exit!\n");
}

int main(void)
{
	//创建线程，默认属性，指定例程和传入参数
	pthread_t tid;
	pthread_create(&tid,NULL,routine,(void*)"main");
	
	//阻塞等待指定的线程退出，并获取退出值
	void *p = NULL;
	pthread_join(tid,&p);
	printf("join pthread msg:%s",(char*)p);
	
	return 0;
}










