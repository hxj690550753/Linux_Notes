#include "pipe.h"
#include <unistd.h>		//无名管道PIPE
#include <sys/types.h>	//有名管道FIFO
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd_WR[2];				
	int *fd_read = &(fd_WR[0]);		
	int *fd_write = &(fd_WR[1]);	

	if(pipe(fd_WR) == -1)
	{
		perror("[FLASE] pipe()\n");
		exit(1);
	}
	
	pid_t x = fork();
	
	if(x == 0)
	{
		char *buf = "I'm child";
		write_pipe(*fd_write,buf,strlen(buf));
	}
	
	if(x > 0)
	{
		read_pipe(*fd_read,100);
		int statues;
		wait(&statues);
	}
	return 0;
}