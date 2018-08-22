#include "dlist.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
	int d[10] = {-2,5,100,78,62,-12,-79,-711,0,123};
	dink_list head = init_list();
	
	int i = 0;
	for(;i<10;++i)
	{
		dink_list new = new_node(d[i],NULL,NULL);
		if(i%2==0)
			insert_next(head,new);
		else
			insert_prev(head,new);
		show(head);
	}

	dink_list _node = find_node(head,d[8]);
	dink_list node_ = find_node(head,d[2]);
	printf("move_next src=%d,dest=%d\n",node_->data,_node->data);
	move_next(_node,node_);
	show(head);
	
	printf("move_prev src=%d,dest=%d\n",node_->data,_node->data);
	move_prev(_node,node_);
	show(head);
	
	for(i = 0; i<10; i+=2)
	{
		dink_list node = find_node(head,d[i]);
		if(NULL != node)
		{
			remove_node(node);
			printf("[OK] remove\n");
			show(head);
		}
		else
		{
			printf("[FLASE] remove\n");
		}
	}

	return 0;
}