#include "link_stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/**
  * @brief  初始化一个空的链表栈的管理结构体
  *			理论上链表没有指定大小，大小为内存大小
  * @param  None
  * @retval 如果内存足够，返回管理结构体结构体的指针，否则返回NULL
  */
struct link_stack* init_stack(void)
{	
	//1.开辟管理结构体
	struct link_stack* s = (struct link_stack*)malloc(sizeof(struct link_stack));
	if(NULL == s)
		return NULL;
	
	//2.管理结构体指向空栈
	s->top = NULL;
	s->size = 0;
	
	return s;
}

/**
  * @brief  新建一个栈节点
  * @param  data：栈节点数据
  * @retval 如果内存足够，返回栈节点的指针，否则返回NULL
  */
struct stack_node* new_node(data_type data)
{
	struct stack_node* new = (struct stack_node*)malloc(sizeof(struct stack_node));
	if(NULL == new)
		return NULL;
	
	new->data = data;
	new->next = NULL;
	return new;
}


  /**
  * @brief  判断栈是否空
  * @param  s:栈的管理结构体
  * @retval 如果栈已空，返回true，否则返回false
  */
bool stack_empty(struct link_stack* s)
{
	if(NULL == s)
		return false;
	return (s->top == NULL)?true:false;
}

/**
  * @brief  把一个元素压栈
  * @param  s:栈的管理结构体
  * @param  new:待压栈的节点
  * @retval 如果内存已满，返回false，否则返回true
  */
bool push_stack(struct link_stack* s, struct stack_node* new)
{
	if(NULL == s || NULL == new)
		return false;
	
	new->next = s->top;
	s->top = new;
	s->size++;
	return true;
}

/**
  * @brief  把一个元素弹出栈外
  * @param  s:栈的管理结构体
  * @param  old:接收出栈的节点指针的指针
  * @retval 如果栈为空，返回false，同时不操作data，否则返回true，对data赋值
  */
bool pop_stack(struct link_stack* s, struct stack_node** old)
{
	if(NULL == s || stack_empty(s) || NULL == old)
		return false;
	
	struct stack_node *p = s->top;
	*old = p;
	s->top = p->next;
	s->size--;
	return true;
}

















