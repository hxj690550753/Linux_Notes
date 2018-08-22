#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include <stdbool.h>

#ifndef _MAX_
#define _MAX_
#define MAX(a,b) \
		({\
			typeof(a) _a = a;\
			typeof(b) _b = b;\
			(void)(&_a == &_b);\
			((_a)>(_b)?(_a):(_b));\
		})
#endif

#ifndef _DATA_TYPE_
#define _DATA_TYPE_
typedef int data_type;
#endif

//树节点
struct BST_node{
	data_type data;
	struct BST_node *lchild;
	struct BST_node *rchild;
};

/**
  * @brief  初始化一棵空BST
  * @param  None
  * @retval 返回树节点指针
  */
struct BST_node* BST_init(void);

/**
  * @brief  新建一个树节点
  * @param  data:节点权值
  * @retval 返回树节点指针
  */
struct BST_node* BST_new_node(data_type data);

/**
  * @brief  按照BST规则插入一个节点
  * @param  root:树根节点指针
  * @param  new:待插入的新节点
  * @retval 若插入成功返回root，否则返回NULL
  */
struct BST_node* BST_insert(struct BST_node* root, struct BST_node* new);

/**
  * @brief  在root为根的树中搜索new节点
  * @param  root:树根节点指针
  * @param  data:待匹配的节点的权值
  * @retval 若搜索成功返回该节点指针，否则返回NULL
  */
struct BST_node* BST_search(struct BST_node* root, data_type data);

/**
  * @brief  在root为根的树中删除new节点
  * @param  root:树根节点指针
  * @param  data:待删除的节点的权值
  * @retval 返回值无意义
  */
struct BST_node* BST_remove(struct BST_node* root, data_type data);


/**
  * @brief  获取以root为根的树高
  * @param  root:树根指针
  * @retval 返回树高
  */
int BST_height(struct BST_node* root);

/**
  * @brief  前序遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_pre_travel(struct BST_node* root);

/**
  * @brief  中序遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_mid_travel(struct BST_node* root);

/**
  * @brief  后序遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_post_travel(struct BST_node* root);

/**
  * @brief  层次遍历遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_level_travel(struct BST_node* root);

#endif 

