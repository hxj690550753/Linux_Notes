#ifndef _SEQUENT_QUEUE_H_
#define _SEQUENT_QUEUE_H_

#include <stdbool.h>

typedef int data_type;

//队列管理结构体
struct sequent_queue{
	data_type *queue;
	int front;
	int rear;
	int size;
};

/**
  * @brief  根据给定的size初始化顺序队列，并默认赋值为0
  * @param  size：队列最大容量
  * @retval 返回队列管理结构体的指针
  */
struct sequent_queue* init_queue(int size);

/**
  * @brief  判断队列是否为空（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @retval 若为空，返回true，否则返回false
  */
bool queue_empty(struct sequent_queue *q);

/**
  * @brief  判断队列是否满（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @retval 若满，返回true，否则返回false
  */
bool queue_full(struct sequent_queue *q);

/**
  * @brief  让一个元素入队（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @param  data：待入队的元素
  * @retval 若队列满，返回false，否则插入队列返回true
  */
bool en_queue(struct sequent_queue *q, data_type data);

/**
  * @brief  出队一个元素（队列是循环队列）
  * @param  q：队列管理结构体指针
  * @param  data：接收出队元素的指针
  * @retval 若队列空，返回false，否则出队返回true
  */
bool de_queue(struct sequent_queue *q, data_type *data);



#endif
