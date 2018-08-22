#include "binary_search_tree.h"
#include "sequent_queue.h"
#include <stdlib.h>
#include <stdio.h>


/**
  * @brief  初始化一棵空BST
  * @param  None
  * @retval 返回树节点指针
  */
struct BST_node* BST_init(void)
{
	return NULL;
}

/**
  * @brief  新建一个树节点
  * @param  data:节点权值
  * @retval 返回树节点指针
  */
struct BST_node* BST_new_node(data_type data)
{
	struct BST_node* node = (struct BST_node*)malloc(sizeof(struct BST_node));
	
	if(NULL != node)
	{
		node->lchild = NULL;
		node->rchild = NULL;
		node->data = data;
	}
	
	return node;
}

/**
  * @brief  按照BST规则插入一个节点
  * @param  root:树根节点指针
  * @param  new:待插入的新节点
  * @retval 若插入成功返回root，否则返回NULL
  */
struct BST_node* BST_insert(struct BST_node* root, struct BST_node* new)
{
	//入口检查
	if(NULL == root)
		return new;
	if(NULL == new)
		return root;
	
	//1.比较root与new的data
	//2.若new大，放在root的rchild
	if(new->data > root->data)
	{
		root->rchild = BST_insert(root->rchild,new);
	}
	//3.若new小，放在root的lchild
	else if(new->data < root->data)
	{
		root->lchild = BST_insert(root->lchild,new);
	}
	//4.若相等，不作任何操作
	else if(new->data == root->data)
	{
		printf("%d is already\n",new->data);
	}
	
	return root;
}

/**
  * @brief  在root为根的树中搜索new节点
  * @param  root:树根节点指针
  * @param  data:待匹配的节点的权值
  * @retval 若搜索成功返回该节点指针，否则返回NULL
  */
struct BST_node* BST_search(struct BST_node* root, data_type data)
{
	//入口检查
	if(NULL == root)
		return NULL;
	
	//1.如果new>root，返回右子树
	if(data > root->data)
		return BST_search(root->rchild,data);
	//2.如果new<root，返回左子树
	else if(data < root->data)
		return BST_search(root->lchild,data);
	//3.如果new==root，返回root
	else
		return root;
}

/**
  * @brief  在root为根的树中删除new节点
  * @param  root:树根节点指针
  * @param  data:待删除的节点的权值
  * @retval 返回值无意义
  */
struct BST_node* BST_remove(struct BST_node* root, data_type data)
{
	if(NULL == root)
		return NULL;
	
	//1.寻找待删除的节点
	if(data > root->data)
		root->rchild = BST_remove(root->rchild,data);
	else if(data < root->data)
		root->lchild = BST_remove(root->lchild,data);
	else
	{
		struct BST_node* tmp;
		//2.若删除的节点有左子树，则选最大值节点来代替，然后删除这个节点
		if(NULL != root->lchild)
		{
			//一直往右子树找，找到最右边的就是最大值
			for(tmp=root->lchild; tmp->rchild != NULL; tmp = tmp->rchild);
			//替换
			root->data = tmp->data;
			//删除
			root->lchild = BST_remove(root->lchild,tmp->data);
		}
		//3.若删除的节点有右子树，则选最小的节点来代替，然后释放这个节点
		else if(NULL != root->rchild)
		{
			//一直往左子树找，找到最左边的就是最小值
			for(tmp=root->rchild; tmp->lchild != NULL; tmp = tmp->lchild);
			//替换
			root->data = tmp->data;
			//删除
			root->rchild = BST_remove(root->rchild,tmp->data);			
		}
		//4.若删除的节点没有孩子，直接释放
		else
		{
			free(root);
			root = NULL;
			tmp = NULL;
			return NULL;
		}
	}
	return root;
}

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
void BST_pre_travel(struct BST_node* root)
{
	//入口
	if(NULL == root)
		return;

	BST_pre_travel(root->lchild);
	printf("%d ",root->data);
	BST_pre_travel(root->rchild);
	
}

/**
  * @brief  中序遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_mid_travel(struct BST_node* root)
{
	//入口
	if(NULL == root)
		return;

	printf("%d ",root->data);
	BST_pre_travel(root->lchild);
	BST_pre_travel(root->rchild);	
}

/**
  * @brief  后序遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_post_travel(struct BST_node* root)
{
	//入口
	if(NULL == root)
		return;

	BST_pre_travel(root->lchild);
	BST_pre_travel(root->rchild);
	printf("%d ",root->data);
}

/**
  * @brief  层次遍历遍历树
  * @param  root:树根指针
  * @retval None
  */
void BST_level_travel(struct BST_node* root)
{
	//入口
	if(NULL == root)
		return;
	
	struct sequent_queue* q = init_queue(30);
	struct BST_node* tmp;
	
	//1.root入队
	en_queue(q,root->data);
	//2.队列是否为空，若为空，遍历结束，否则输出队头
	while(!queue_empty(q))
	{
		data_type d = 0;
		de_queue(q,&d);
		printf("%d ",d);
		
		//3.队头的左孩子不为空则入队
		tmp = BST_search(root,d);
		if(NULL != tmp->lchild)
			en_queue(q,tmp->lchild->data);
		//4.队头的右孩子不为空则入队
		if(NULL != tmp->rchild)
			en_queue(q,tmp->rchild->data);
	}

}


