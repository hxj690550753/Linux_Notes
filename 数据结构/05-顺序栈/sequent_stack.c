#include "sequent_stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/**
  * @brief  初始化一个空的顺序栈
  * @param  size：顺序栈的最大容量
  * @retval 如果内存足够，返回顺序栈结构体的指针，否则返回NULL
  */
struct sequent_stack* init_stack(int size)
{
	//入口检查
	if(size<=0)
		return NULL;
	
	//1.开辟管理结构体
	struct sequent_stack* p_s = (struct sequent_stack*)malloc(sizeof(struct sequent_stack));
	if(NULL == p_s)
		return NULL;
	
	//2.开辟栈
	data_type *p_stack = (data_type*)malloc(size*sizeof(data_type));
	if(NULL == p_stack)
	{
		free(p_s);
		return NULL;
	}
	
	//3.给栈赋值0
	memset(p_stack,0,size*sizeof(data_type));
	
	//4.栈加入管理结构体中，并返回
	p_s->stack = p_stack;
	p_s->size = size;		
	p_s->top = -1;				//-1代表空栈
	return p_s;
}


/**
  * @brief  判断栈是否满
  * @param  s:栈的管理结构体
  * @retval 如果栈已满，返回true，否则返回false
  */
bool stack_full(struct sequent_stack* s)
{
	return ((s->top+1) == s->size)?true:false;
}
  
  /**
  * @brief  判断栈是否空
  * @param  s:栈的管理结构体
  * @retval 如果栈已空，返回true，否则返回false
  */
bool stack_empty(struct sequent_stack* s)
{
	return (s->top == -1)?true:false;
}

/**
  * @brief  把一个元素压栈
  * @param  s:栈的管理结构体
  * @param  data:待压栈的数据
  * @retval 如果栈已满，返回false，否则返回true
  */
bool push_stack(struct sequent_stack* s, data_type data)
{
	if(stack_full(s))
		return false;
	
	s->stack[++s->top] = data;
	return true;
}

/**
  * @brief  把一个元素弹出栈外
  * @param  s:栈的管理结构体
  * @param  data:接收出栈的数据
  * @retval 如果栈为空，返回false，同时不操作data，否则返回true，对data赋值
  */
bool pop_stack(struct sequent_stack* s, data_type* data)
{
	if(stack_empty(s))
		return false;
	
	*data = s->stack[s->top--];
	return true;
}

















