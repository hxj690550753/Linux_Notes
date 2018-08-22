#include "link_stack.h"
#include <stdio.h>
#include <stdlib.h>

//利用栈，解决汉诺塔问题
void hanno(int num, struct link_stack *A, struct link_stack *B, struct link_stack *C);

//展示
void show(struct link_stack *A, struct link_stack *B, struct link_stack *C);

int main(void)
{
	//1.定义Hanno数量变量、栈A/B/C指针
	int i;
	int hanno_num = 0;
	struct link_stack* A;
	struct link_stack* B;
	struct link_stack* C;
	
	
	//2.初始化栈A/B/C
	A = init_stack();
	B = init_stack();
	C = init_stack();
	if(A==NULL || B==NULL || C==NULL)
	{
		printf("not enough memory\n");
		return 0;
	}
	
	//3.用户输入Hanno数量
	printf("input:");
	scanf("%d",&hanno_num);
	for(i = 0; i<hanno_num; i++)
	{
		struct stack_node *new = new_node(hanno_num-i);
		push_stack(A,new);
	}
	
	//4.计算并输出
	hanno(hanno_num,A,B,C);
	show(A,B,C);
	
	free(A);
	free(B);
	free(C);
	return 0;
}

//A借助C移动num个到B
void hanno(int num, struct link_stack *A, struct link_stack *B, struct link_stack *C)
{
	if(num<=0)
		return;
	
	struct stack_node* tmp;
	
	//1.把n-1个塔从A借助B移动到C
	hanno(num-1,A,C,B);
	printf("press\n");
	getchar();
	show(A,B,C);
	//2.把A中最底层的塔移动到B
	pop_stack(A,&tmp);
	push_stack(B,tmp);
	//3.把C中n-1个塔借助A移动到B
	hanno(num-1,C,B,A);
}

//展示
void show(struct link_stack *A, struct link_stack *B, struct link_stack *C)
{
	int maxlen;
	int len;
	
	maxlen = A->size > B->size ? A->size : B->size;
	maxlen = maxlen > C->size ? maxlen : C->size;
	len = maxlen;
	
	struct stack_node *t1 = A->top;
	struct stack_node *t2 = B->top;
	struct stack_node *t3 = C->top;
	
	int i;
	for(i = 0; i<maxlen; i++)
	{
		if(t1 != NULL && len <= A->size)
		{
			printf("%d",t1->data);
			t1 = t1->next;
		}
		printf("\t");
		
		if(t2 != NULL && len <= B->size)
		{
			printf("%d",t2->data);
			t2 = t2->next;
		}
		printf("\t");
		
		if(t3 != NULL && len <= C->size)
		{
			printf("%d",t3->data);
			t3 = t3->next;
		}
		printf("\n");
		
		len--;
	}
	printf("A\tB\tC\n------------\n");
	
}




