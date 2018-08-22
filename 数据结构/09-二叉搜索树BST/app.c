#include "binary_search_tree.h"
#include <stdio.h>
int main(void)
{
	struct BST_node* root = BST_init();
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n>0)
		{
			struct BST_node* node = BST_new_node(n);
			root = BST_insert(root,node);
			BST_pre_travel(root);
			printf("\n");
			BST_level_travel(root);
		}
		if(n<0)
		{
			root = BST_remove(root,-n);
			BST_pre_travel(root);
			printf("\n");
		}
		if(n==0)
			break;
	}
	return 0;
}