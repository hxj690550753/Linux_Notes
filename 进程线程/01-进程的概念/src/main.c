#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
	pid_t x;
	x = fork();
	
	if(x > 0)
	{
		printf("[%d]:father\n",(int)getpid());
		int status;
		wait(&status);
	}
	if(x == 0)
	{
		printf("[%d]:be fork()\n",(int)getpid());
		execl("./child_code","child_code",NULL);
		printf("[%d]:again print\n",(int)getpid());	//若execl成功，此语句被覆盖
	}
}