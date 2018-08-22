#include "slist.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
  * @brief  创建一个空链表，只有一个节点head，它的next指向NULL
  * @param  None
  * @retval 返回头节点地址singly_list
  */
singly_list init_list(void)
{
	singly_list head = (singly_list)malloc(sizeof(slist_node));
	if(NULL != head)
	{
		head->next = NULL;
	}
	
	return head;
}

/**
  * @brief  判断链表是否为空
  * @param  head：待判断的链表
  * @retval 若为空，返回true，否则返回false
  */
bool list_is_empty(singly_list head)
{
	//入口判断
	assert(NULL != head);
	
	//1.判断nex
	if(NULL == head->next)
		return true;
	return false;
}


/**
  * @brief  在链表head中查找第一次出现data的节点地址
  * @param  head：待查找的链表头节点
  * @param  data：需要匹配的数据
  * @retval 若查到成功就返回节点地址，否则返回NULL
  */
singly_list find_node(singly_list head, data_type data)
{
	//入口判断
	assert(NULL != head);
	
	//1.空链表判断
	singly_list ret = NULL;
	
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return ret;
	}

	//2.循环查找
	singly_list p = head->next;
	while(NULL != p)
	{
		if(p->data == data)
		{
			ret = p;
			break;
		}
		p = p->next;
	}
	return ret;
}

/**
  * @brief  在节点old及其后驱之间插入节点new
  * @param  old：需要插入的位置的前驱节点地址
  * @param  new：待插入的节点地址
  * @retval None
  */
void insert_node(singly_list old, singly_list new)
{
	//入口判断
	assert((NULL != old) && (NULL != new));
	
	//1.new指向old的后驱
	new->next = old->next;
	
	//2.old指向new
	old->next = new;
}

/**
  * @brief  在链表head中删除一个节点node
  * @param  head：需要删除节点的链表
  * @param  node：待删除的节点地址
  * @retval 成功删除返回true，否则返回false
  */
bool remove_node(singly_list head, singly_list node)
{
	//入口判断
	assert((NULL != head) && (NULL != node));
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return false;
	}
	
	//1.记录head
	singly_list p = head;
	
	//2.找到node的前驱
	while((NULL != p) && (p->next != node))
	{
		p = p->next;
	}
	
	//3.改变指针指向
	if(NULL == p)
		return false;
	else
	{
		p->next = node->next;
		node->next = NULL;
	}
	
	return true;
}

/**
  * @brief  在链表head中，把节点node移动到节点an_node的后面
  * @param  head：需要移动节点的链表
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_node(singly_list head, singly_list node, singly_list an_node)
{
	//入口判断
	assert((NULL != head) && (NULL != node) && (NULL != an_node));
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return;
	}
	
	//1.记录node
	singly_list p = node;
	
	//2.删除node
	if(!remove_node(head,p))
	{
		printf("[FLASE] not this node\n");
		return;		
	}
	
	//3.在an_node后插入node
	insert_node(an_node,p);
}


/**
  * @brief  创建新节点
  * @param  data：节点数据
  * @param  next：新节点的下一个指向
  * @retval 新创建的节点
  */
singly_list new_node(data_type data, singly_list next)
{
	singly_list node = (singly_list)malloc(sizeof(slist_node));
	
	if(NULL != node)
	{
		node->data = data;
		node->next = next;
	}
	return node;
}

/**
  * @brief  显示链表
  * @param  head：链表头节点
  * @retval None
  */
void show(singly_list head)
{
	assert(NULL != head);
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return;
	}
	
	singly_list p = head->next;
	
	int i = 0;
	while(NULL != p)
	{
		printf("%s%d",i==0?"":"-->",p->data);
		p = p->next;
		i++;
	}
	printf("\n");
}
