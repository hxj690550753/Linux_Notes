#include "link_queue.h"
#include <stdio.h>
#include <stdlib.h>

//展示
void show(struct link_queue *q);

int main(void)
{
	//1.队列管理结构体变量、用户输入缓冲变量、容量变量
	struct link_queue *q = NULL;
	int operation = 'e';
	int data = 0;
	int c;
	struct queue_node *node;
	
	//2.初始化队列
	q = init_queue();
	
	//3.用户输入eXX就把XX入队,用户输入dXX就出队一个元素,输入q退出app
	while(1)
	{
		printf("\ninput----eXX/d/q:");
		operation = getchar();
		if(operation != 'q')
		{
			if(operation == 'e')
			{
				scanf("%d",&data);
				node = new_node(data);
				en_queue(q,node);
			}
			if(operation == 'd')
			{
				if(de_queue(q,&node))
				{
					printf("\noutput data:%d\n",node->data);
					free(node);
					node = NULL;
				}
			}
			//清空缓冲区
			while ((c = getchar()) != EOF && c != '\n');
			show(q);
		}
		else
			break;
	}
	free(q);
	return 0;
}

void show(struct link_queue *q)
{
	if(queue_empty(q))
		return;
	
	struct queue_node *tmp = q->front;
	int flag = 0;
	
	
	while(tmp != NULL)
	{
		printf("%s%d",flag==0?"":"-->",tmp->data);
		tmp = tmp->next;
		flag = 1;
	}
	printf("\n");
}