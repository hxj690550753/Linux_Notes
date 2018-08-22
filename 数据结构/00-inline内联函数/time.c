#include <time.h>
#include <stdio.h>

int Max(int a, int b)
{
	return a>b ? a : b;				
}

int main(void)
{
	//clock_t是clock()函数返回的变量类型
	clock_t start;		
	clock_t stop;     
	clock_t ret = 0;	
	int i;
	
	for(i = 0; i<100000; ++i)
	{
		//记录ticks
		start = clock();
		int a = 1;
		int b = 2;
		int c = a>b ? a : b;
		stop = clock();	
		//计算
		ret += (stop-start);	
	}
	//输出均值
	printf("ret_avg %lf ticks\n",(double)ret/100000.0);
}



