#include "dlist.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
  * @brief  创建一个空链表，只有一个节点head，它的next指向自身
  * @param  None
  * @retval 返回头节点地址dink_list
  */
dink_list init_list(void)
{
	dink_list head = (dink_list)malloc(sizeof(dlist_node));
	if(NULL != head)
	{
		head->next = head;
		head->prev = head;
	}
	
	return head;
}

/**
  * @brief  判断链表是否为空
  * @param  head：待判断的链表
  * @retval 若不为空，返回true，否则返回flase
  */
bool list_is_empty(dink_list head)
{
	//入口判断
	assert(NULL != head);
	
	if((head->next == head) && (head->prev == head))
		return true;
	return false;
}


/**
  * @brief  在链表head中查找第一次出现data的节点地址
  * @param  head：待查找的链表头节点
  * @param  data：需要匹配的数据
  * @retval 若查到成功就返回节点地址，否则返回NULL
  */
dink_list find_node(dink_list head, data_type data)
{
	//入口判断
	assert(NULL != head);
	
	//1.空链表判断
	dink_list ret = NULL;
	
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return ret;
	}

	//2.循环查找
	dink_list p = head->next;
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
void insert_next(dink_list old, dink_list new)
{
	//入口判断
	assert((NULL != old) && (NULL != new));
	
	//1.new的next指向old的next
	new->next = old->next;
	
	//2.new的prev指向old
	new->prev = old;
	
	//3.old的next的prev指向new
	old->next->prev = new;
	
	//4.old的next指向new
	old->next = new;
}

/**
  * @brief  在节点old及其前驱之间插入节点new
  * @param  old：需要插入的位置的前驱节点地址
  * @param  new：待插入的节点地址
  * @retval None
  */
void insert_prev(dink_list old, dink_list new)
{
	//入口判断
	assert((NULL != old) && (NULL != new));

	
	//1.new的prev指向old的prev
	new->prev = old->prev;
	
	//2.new的next指向old
	new->next = old;
	
	//3.old的prev的next指向new
	old->prev->next = new;
	
	//4.old的prev指向new
	old->prev = new;
}

/**
  * @brief  根据node直接得到前后驱，然后就可以删除节点node
  * @param  node：待删除的节点地址
  * @retval None
  */
void remove_node(dink_list node)
{
	//入口判断
	assert(NULL != node);
	if(list_is_empty(node))
	{
		printf("[FLASE] List is NULL\n");
		return;
	}
	
	//1.node的prev的next指向node的next
	node->prev->next = node->next;
	
	//2.node的next的prev指向node的prev
	node->next->prev = node->prev;
	
	//3.node的next和prev赋值NULL
	node->next = NULL;
	node->prev = NULL;
}

/**
  * @brief  把节点node移动到节点an_node的前面
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_prev(dink_list node, dink_list an_node)
{
	//入口判断
	assert((NULL != node) && (NULL != an_node));
	
	//1.删除节点node
	remove_node(node);
	
	//2.移动node到an_node后面
	insert_prev(an_node,node);
}

/**
  * @brief  把节点node移动到节点an_node的后面
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_next(dink_list node, dink_list an_node)
{
	//入口判断
	assert((NULL != node) && (NULL != an_node));
	
	//1.删除节点node
	remove_node(node);
	
	//2.移动node到an_node后面
	insert_next(an_node,node);
}


/**
  * @brief  创建新节点
  * @param  data：节点数据
  * @param  next：新节点的下一个指向
  * @param  prev: 新节点的前一个指向
  * @retval 新创建的节点
  */
dink_list new_node(data_type data, dink_list prev, dink_list next)
{
	dink_list node = (dink_list)malloc(sizeof(dlist_node));
	
	if(NULL != node)
	{
		node->data = data;
		node->next = next;
		node->prev = prev;
	}
	return node;
}

/**
  * @brief  显示链表
  * @param  head：链表头节点
  * @retval None
  */
void show(dink_list head)
{
	assert(NULL != head);
	if(list_is_empty(head))
	{
		printf("[FLASE] List is NULL\n");
		return;
	}
	
	dink_list p = head->next;
	
	int i = 0;
	while(head != p)
	{
		printf("%s%d",i==0?"":"<->",p->data);
		p = p->next;
		i++;
	}
	printf("\n");
}
