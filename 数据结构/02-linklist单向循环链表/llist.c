#include "llist.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
  * @brief  创建一个空链表，只有一个节点head，它的next指向自身
  * @param  None
  * @retval 返回头节点地址link_list
  */
link_list init_list(void)
{
	link_list head = (link_list)malloc(sizeof(llist_node));
	if(NULL != head)
	{
		head->next = head;
	}
	
	return head;
}

/**
  * @brief  判断链表是否为空
  * @param  head：待判断的链表
  * @retval 若不为空，返回true，否则返回flase
  */
bool list_is_empty(link_list head)
{
	//入口判断
	assert(NULL != head);
	
	if(head->next == head)
		return true;
	return false;
}


/**
  * @brief  在链表head中查找第一次出现data的节点地址
  * @param  head：待查找的链表头节点
  * @param  data：需要匹配的数据
  * @retval 若查到成功就返回节点地址，否则返回NULL
  */
link_list find_node(link_list head, data_type data)
{
	//入口判断
	assert(NULL != head);
	
	//1.空链表判断
	link_list ret = NULL;
	
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return ret;
	}

	//2.循环查找
	link_list p = head->next;
	while(head != p)
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
void insert_node(link_list old, link_list new)
{
	//入口判断
	assert((NULL != old) && (NULL != new));
	
	//1.new指向old的后驱
	new->next = old->next;
	
	//2.old指向new
	old->next = new;
}

/**
  * @brief  根据node循环搜索前驱，然后就可以删除节点node
  * @param  node：待删除的节点地址
  * @retval 成功删除返回true，否则返回false
  */
bool remove_node(link_list node)
{
	//入口判断
	assert(NULL != node);
	if(list_is_empty(node))
	{
		printf("[FLASE] List is NULL\n");
		return false;
	}
	
	//1.记录node
	link_list p = node;
	
	//2.找到node的前驱
	while(p->next != node)
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
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_node(link_list node, link_list an_node)
{
	//入口判断
	assert((NULL != node) && (NULL != an_node));
	
	//1.记录node
	link_list p = node;
	
	//2.删除node
	if(!remove_node(p))
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
link_list new_node(data_type data, link_list next)
{
	link_list node = (link_list)malloc(sizeof(llist_node));
	
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
void show(link_list head)
{
	assert(NULL != head);
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return;
	}
	
	link_list p = head->next;
	
	int i = 0;
	while(head != p)
	{
		printf("%s%d",i==0?"":"-->",p->data);
		p = p->next;
		i++;
	}
	printf("\n");
}
