#include "link_queue.h"
#include <stdlib.h>
#include <string.h>
/**
  * @brief  初始化链表队列，头尾指针都指向NULL
  *			理论上链表无大小，其大小取决于内存，于是没有判断满操作
  * @param  None
  * @retval 返回队列管理结构体的指针
  */
struct link_queue* init_queue(void)
{
	//1.开辟管理结构体指针
	struct link_queue* q = (struct link_queue*)malloc(sizeof(struct link_queue));
	
	//2.开辟队列并赋值0
	if(NULL != q)
	{
		q->front = NULL;
		q->rear = NULL;
		q->size = 0;
	}
	
	return q;
}

/**
  * @brief  判断队列是否为空（链表队列）
  * @param  q：队列管理结构体指针
  * @retval 若为空，返回true，否则返回false
  */
bool queue_empty(struct link_queue *q)
{
	if(q->size == 0)
		return true;
	return false;
}


/**
  * @brief  让一个元素入队（链表队列）
  * @param  q：队列管理结构体指针
  * @param  new：待入队的元素的指针
  * @retval 若内存满，返回false，否则插入队列返回true
  */
bool en_queue(struct link_queue *q, struct queue_node *new)
{
	//入口检查
	if(NULL == q || NULL == new)
		return false;
	
	//1.插入队列
	if(queue_empty(q))					//第一个元素特别处理
		q->front = q->rear = new;
	else
	{
		q->rear->next = new;
		q->rear = new;
	}
	q->size++;
	
	return true;
}

/**
  * @brief  出队一个元素（链表队列）
  * @param  q：队列管理结构体指针
  * @param  data：接收出队元素的指针
  * @retval 若队列空，返回false，否则出队返回true
  */
bool de_queue(struct link_queue *q, struct queue_node **old)
{
	//入口判断
	if(NULL == q || NULL == old)
		return false;
	
	//1.判断队列是否为空
	if(queue_empty(q))
		return false;
	
	//2.元素出队
	*old = q->front;
	q->size--;
	if(queue_empty(q))				//全部出队
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;	//未全部出队
	
	return true;
}

/**
  * @brief  新建一个队列节点
  * @param  data：队列节点元素
  * @retval 若内存满，返回NULL，否则返回节点指针
  */
struct queue_node *new_node(data_type data)
{
	struct queue_node *new = (struct queue_node *)malloc(sizeof(struct queue_node ));
	
	if(NULL != new)
	{
		new->data = data;
		new->next = NULL;
	}
}


