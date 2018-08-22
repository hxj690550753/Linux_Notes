#include "sequent_stack.h"
#include <stdio.h>

//实现把10进制转换为8进制（只处理正数）

int main(void)
{
	//1.定义10/8进制、管理结构体变量
	int Ddata = -1;
	int Odata = 0;
	const int size = 10;
	struct sequent_stack* s = NULL;
	
	//2.初始化空栈
	s = init_stack(size);
	
	//3.用户输入10进制
	while(Ddata<0)
	{
		printf("input:");
		scanf("%d",&Ddata);		
	}
	
	//4.转换
	do{
		push_stack(s,Ddata%8);
		Ddata /= 8;
	}while(Ddata);
	
	
	//5.输出
	printf("output:");
	while(!stack_empty(s))
	{
		pop_stack(s,&Odata);
		printf("%d",Odata);
	}
	printf("\n");
	
	return 0;
}

