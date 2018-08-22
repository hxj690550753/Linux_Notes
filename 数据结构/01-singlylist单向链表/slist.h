#ifndef SLIST_H_
#define SLIST_H_

#define _BOOL_

//bool定义
#ifdef _BOOL_
enum bool_type{
	false = 0,
	true,
};
typedef enum bool_type bool;
#endif


//数据类型
typedef int data_type;

//节点定义
struct node{
	data_type data;
	struct node *next;
};

//类型起名
typedef struct node 	slist_node;
typedef struct node* 	singly_list;



/**
  * @brief  创建一个空链表，只有一个节点head，它的next指向NULL
  * @param  None
  * @retval 返回头节点地址singly_list
  */
singly_list init_list(void);

/**
  * @brief  判断链表是否为空
  * @param  head：待判断的链表
  * @retval 若不为空，返回true，否则返回flase
  */
bool list_is_empty(singly_list head);

/**
  * @brief  根据数据data在链表head中查找对应的节点地址
  * @param  head：待查找的链表头节点
  * @param  data：需要匹配的数据
  * @retval 返回查到到的节点地址/NULL
  */
singly_list find_node(singly_list head, data_type data);

/**
  * @brief  在节点old及其后驱之间插入节点new
  * @param  old：需要插入的位置的前驱节点地址
  * @param  new：待插入的节点地址
  * @retval None
  */
void insert_node(singly_list old, singly_list new);

/**
  * @brief  在链表head中删除一个节点node
  * @param  head：需要删除节点的链表
  * @param  node：待删除的节点地址
  * @retval 成功删除返回true，否则返回flase
  */
bool remove_node(singly_list head, singly_list node);

/**
  * @brief  在链表head中，把节点node移动到节点an_node的后面
  * @param  head：需要移动节点的链表
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_node(singly_list head, singly_list node, singly_list an_node);

/**
  * @brief  创建新节点
  * @param  data：节点数据
  * @param  next：新节点的下一个指向
  * @retval 新创建的节点
  */
singly_list new_node(data_type data, singly_list next);

/**
  * @brief  显示链表
  * @param  head：链表头节点
  * @retval None
  */
void show(singly_list head);

#endif