#include "llist.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
	int d[10] = {-2,5,100,78,62,-12,-79,-711,0,123};
	link_list head = init_list();
	
	int i = 0;
	for(;i<10;++i)
	{
		link_list new = new_node(d[i],NULL);
		insert_node(head,new);
		show(head);
	}

	link_list _node = find_node(head,d[4]);
	link_list node_ = find_node(head,d[2]);
	move_node(_node,node_);
	show(head);
	
	for(i = 0; i<10; i+=2)
	{
		link_list node = find_node(head,d[i]);
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