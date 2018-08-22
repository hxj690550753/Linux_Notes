#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_

#include <stdbool.h>

typedef int data_type;

//队列节点
struct queue_node{
	data_type data;
	struct queue_node *next;
};

//队列管理结构体
struct link_queue{
	struct queue_node *front;
	struct queue_node *rear;
	int size;
};

/**
  * @brief  初始化链表队列，头尾指针都指向NULL
  *			理论上链表无大小，其大小取决于内存，于是没有判断满操作
  * @param  None
  * @retval 返回队列管理结构体的指针
  */
struct link_queue* init_queue(void);

/**
  * @brief  判断队列是否为空（链表队列）
  * @param  q：队列管理结构体指针
  * @retval 若为空，返回true，否则返回false
  */
bool queue_empty(struct link_queue *q);


/**
  * @brief  让一个元素入队（链表队列）
  * @param  q：队列管理结构体指针
  * @param  new：待入队的元素的指针
  * @retval 若内存满，返回false，否则插入队列返回true
  */
bool en_queue(struct link_queue *q, struct queue_node *new);

/**
  * @brief  出队一个元素（链表队列）
  * @param  q：队列管理结构体指针
  * @param  data：接收出队元素的指针
  * @retval 若队列空，返回false，否则出队返回true
  */
bool de_queue(struct link_queue *q, struct queue_node **old);

/**
  * @brief  新建一个队列节点
  * @param  data：队列节点元素
  * @retval 若内存满，返回NULL，否则返回节点指针
  */
struct queue_node *new_node(data_type data);



#endif
