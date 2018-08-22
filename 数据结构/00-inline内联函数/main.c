#include <stdio.h>

inline int max(int a, int b)
{
	return ((a>b)?a:b);
}

void A1(void);
void A2(void);
extern void test(void);

int main(void)
{
	int max_val = max(-100,120);
	printf("max=%d",max_val);
	A1();
	A2();
	test();
	return 0;
}

void A1(void)
{
	int max_val = max(-100,120);
	printf("max=%d",max_val);
}
void A2(void)
{
	int max_val = max(-100,120);
	printf("max=%d",max_val);
}





