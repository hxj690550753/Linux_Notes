#ifndef DLIST_H_
#define DLIST_H_

#ifndef _BOOL_
#define _BOOL_
#endif

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
	struct node *prev;
	struct node *next;
};

//类型起名
typedef struct node 	dlist_node;
typedef struct node* 	dink_list;



/**
  * @brief  创建一个空链表，只有一个节点head，它的next指向NULL
  * @param  None
  * @retval 返回头节点地址dink_list
  */
dink_list init_list(void);

/**
  * @brief  判断链表是否为空
  * @param  head：待判断的链表
  * @retval 若不为空，返回true，否则返回flase
  */
bool list_is_empty(dink_list head);

/**
  * @brief  在链表head中查找第一次出现data的节点地址
  * @param  head：待查找的链表头节点
  * @param  data：需要匹配的数据
  * @retval 若查到成功就返回节点地址，否则返回NULL
  */
dink_list find_node(dink_list head, data_type data);

/**
  * @brief  在节点old及其后驱之间插入节点new
  * @param  old：需要插入的位置的前驱节点地址
  * @param  new：待插入的节点地址
  * @retval None
  */
void insert_next(dink_list old, dink_list new);

/**
  * @brief  在节点old及其前驱之间插入节点new
  * @param  old：需要插入的位置的前驱节点地址
  * @param  new：待插入的节点地址
  * @retval None
  */
void insert_prev(dink_list old, dink_list new);

/**
  * @brief  根据node直接得到前后驱，然后就可以删除节点node
  * @param  node：待删除的节点地址
  * @retval None
  */
void remove_node(dink_list node);

/**
  * @brief  把节点node移动到节点an_node的前面
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_prev(dink_list node, dink_list an_node);

/**
  * @brief  把节点node移动到节点an_node的后面
  * @param  node：待移动的节点node地址
  * @param  an_node：需要移动到的节点an_node地址
  * @retval None
  */
void move_next(dink_list node, dink_list an_node);

/**
  * @brief  创建新节点
  * @param  data：节点数据
  * @param  next：新节点的下一个指向
  * @param  prev: 新节点的前一个指向
  * @retval 新创建的节点
  */
dink_list new_node(data_type data, dink_list prev, dink_list next);

/**
  * @brief  显示链表
  * @param  head：链表头节点
  * @retval None
  */
void show(dink_list head);

#endif