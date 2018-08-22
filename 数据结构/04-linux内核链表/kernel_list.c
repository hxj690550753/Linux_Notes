#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#include "list.h"		//内核链表

typedef int data_type;

#define SIZE	20
enum operation{
	insert,
	delete,
	move_p,
	move_n,
	quit,
};

typedef struct node{
	data_type data;
	struct list_head list;	//内嵌链表
}listnode,*linklist;

/**
 * 创建并初始化一个具有表头的空链表
 */

linklist init_list(void)
{
	linklist head = malloc(sizeof(listnode));
	if(NULL != head)
	{
		INIT_LIST_HEAD(&head->list);	//使用内核源码
	}
	return head;
}

/**
 * 创建并初始化一个新节点
 * @data 新节点的数据
 */
linklist new_node(data_type data)
{
	linklist new = malloc(sizeof(listnode));
	if(NULL != new)
	{
		new->data = data;
		new->list.prev = NULL;
		new->list.next = NULL;
	}
	return new;
}

/**
 * 显示链表
 * @head 具有表头的结构体
 */
void show(linklist head)
{
	linklist tmp;
	struct list_head *pos;
	int flag = 0;
	
	list_for_each(pos,&head->list)
	{
		tmp = list_entry(pos,listnode,list);	//内核源码，得到大结构体指针
		printf("%s",flag==0?"":"-->");
		printf("%d",tmp->data);
		flag=1;
	}
}

/**
 * 显示链表
 * @data 指定的数据
 * @head 具有表头的结构体
 */
linklist find_node(data_type data, linklist head)
{
	if(list_empty(&head->list))
		return NULL;
	
	linklist pos;
	
	list_for_each_entry(pos,&head->list,list)
	{
		if(pos->data == data)
			return pos;
	}
	return NULL;
}

int main(void)
{
	int d[10] = {-2,5,100,78,62,-12,-79,-711,0,123};
	linklist head = init_list();
	
	int i = 0;
	for(;i<10;++i)
	{
		linklist new = new_node(d[i]);
		if(i%2==0)
			list_add_tail(&new->list,&head->list);
		else
			list_add(&new->list,&head->list);
		show(&head->list);
	}

	linklist _node = find_node(&head->list,d[8]);
	linklist node_ = find_node(&head->list,d[2]);
	printf("move_next src=%d,dest=%d\n",node_->data,_node->data);
	list_move(&_node->list,&node_->list);
	show(&head->list);
	
	printf("move_prev src=%d,dest=%d\n",node_->data,_node->data);
	list_move_tail(&_node->list,&node_->list);
	show(&head->list);
	
	for(i = 0; i<10; i+=2)
	{
		linklist node = find_node(d[i],head);
		if(NULL != node)
		{
			list_del(&node->list);
			printf("[OK] remove\n");
			free(node);
			show(&head->list);
		}
		else
		{
			printf("[FLASE] remove\n");
		}
	}

	return 0;
}













