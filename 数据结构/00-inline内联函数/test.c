#include <stdio.h>

extern inline int max(int a, int b);

int test(void)
{
	int m = max(-100,120);
	printf("m=%d\n",m);
}