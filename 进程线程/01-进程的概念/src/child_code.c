#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	printf("[%d]:child\n",(int)getpid());
	exit(0);
}