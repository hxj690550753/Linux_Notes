#include "sequent_queue.h"
#include <stdlib.h>
#include <string.h>

/**
  * @brief  根据给定的size初始化顺序队列，并默认赋值为0
  * @param  size：队列最大容量
  * @retval 返回队列管理结构体的指针
  */
struct sequent_queue* init_queue(int size)
{
	//入口检查
	if(size<=0)
		return NULL;
	
	//1.开辟管理结构体指针
	struct sequent_queue* q = (struct sequent_queue*)malloc(sizeof(struct sequent_queue));
	
	//2.开辟队列并赋值0
	if(NULL != q)
	{
		q->queue = (data_type*)malloc(size*sizeof(data_type));
		if(NULL != q->queue)
		{
			memset(q->queue,0,size*sizeof(data_type));
			q->front = 0;
			q->rear = 0;
			q->size = size;
		}
	}
	
	return q;
}

/**
  * @brief  判断队列是否为空（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @retval 若为空，返回true，否则返回false
  */
bool queue_empty(struct sequent_queue *q)
{
	if(NULL == q || q->front != q->rear)
		return false;
	return true;
}

/**
  * @brief  判断队列是否满（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @retval 若满，返回true，否则返回false
  */
bool queue_full(struct sequent_queue *q)
{
	if(NULL == q || (q->rear+1)%q->size != q->front)
		return false;
	return true;
}

/**
  * @brief  让一个元素入队（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @param  data：待入队的元素
  * @retval 若队列满，返回false，否则插入队列返回true
  */
bool en_queue(struct sequent_queue *q, data_type data)
{
	//入口检查
	if(NULL == q)
		return false;
	
	//1.判断是否满队
	if(queue_full(q))
		return false;
	
	//2.插入队列
	q->rear = (q->rear+1)%q->size;
	q->queue[q->rear] = data;
	return true;
}

/**
  * @brief  出队一个元素（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @param  data：接收出队元素的指针
  * @retval 若队列空，返回false，否则出队返回true
  */
bool de_queue(struct sequent_queue *q, data_type *data)
{
	//入口判断
	if(NULL == q || NULL == data)
		return false;
	
	//1.判断队列是否为空
	if(queue_empty(q))
		return false;
	
	//2.元素出队
	q->front = (q->front+1)%q->size;
	*data = q->queue[q->front];
	return true;
}


