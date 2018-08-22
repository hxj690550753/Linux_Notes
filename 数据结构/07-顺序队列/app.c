#include "sequent_queue.h"
#include <stdio.h>

//展示
void show(struct sequent_queue *q);

int main(void)
{
	//1.队列管理结构体变量、用户输入缓冲变量、容量变量
	struct sequent_queue *q = NULL;
	int operation = 'e';
	int data = 0;
	int c;
	const int size = 10;
	
	//2.初始化队列
	q = init_queue(size);
	
	//3.用户输入eXX就把XX入队,用户输入dXX就出队一个元素,输入q退出app
	while(1)
	{
		printf("\ninput----eXX/d/q\n");
		operation = getchar();
		if(operation != 'q')
		{
			if(operation == 'e')
			{
				scanf("%d",&data);
				en_queue(q,data);
			}
			if(operation == 'd')
			{
				de_queue(q,&data);
				printf("\noutput data:%d\n",data);
			}
			//清空缓冲区
			while ((c = getchar()) != EOF && c != '\n');
			show(q);
		}
		else
			break;
	}
	return 0;
}

void show(struct sequent_queue *q)
{
	if(queue_empty(q))
		return;
	
	
	int tmp = (q->front+1)%q->size;
	int flag = 0;
	
	
	while(tmp != q->rear)
	{
		printf("%s%d",flag==0?"":"-->",q->queue[tmp]);
		tmp = (tmp+1)%q->size;
		flag = 1;
	}
	printf("%s%d",flag==0?"":"-->",q->queue[tmp]);
}