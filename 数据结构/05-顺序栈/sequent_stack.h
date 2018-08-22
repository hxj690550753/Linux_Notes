#ifndef _SEQUENT_STACK_H_
#define _SEQUENT_STACK_H_

#include <stdbool.h>

typedef int data_type;

struct sequent_stack{
	data_type *stack;
	int size;
	int top;
};

/**
  * @brief  初始化一个空的顺序栈
  * @param  size：顺序栈的最大容量
  * @retval 如果内存足够，返回顺序栈结构体的指针，否则返回NULL
  */
struct sequent_stack* init_stack(int size);

/**
  * @brief  判断栈是否满
  * @param  s:栈的管理结构体
  * @retval 如果栈已满，返回true，否则返回flash
  */
bool stack_full(struct sequent_stack* s);
  
  /**
  * @brief  判断栈是否空
  * @param  s:栈的管理结构体
  * @retval 如果栈已空，返回true，否则返回flash
  */
bool stack_empty(struct sequent_stack* s);

/**
  * @brief  把一个元素压栈
  * @param  s:栈的管理结构体
  * @param  data:待压栈的数据
  * @retval 如果栈已满，返回flash，否则返回true
  */
bool push_stack(struct sequent_stack* s, data_type data);

/**
  * @brief  把一个元素弹出栈外
  * @param  s:栈的管理结构体
  * @param  data:接收出栈的数据
  * @retval 如果栈为空，返回flash，同时不操作data，否则返回true，对data赋值
  */
bool pop_stack(struct sequent_stack* s, data_type* data);


#endif






