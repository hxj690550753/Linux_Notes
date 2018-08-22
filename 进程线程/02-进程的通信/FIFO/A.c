#include "fifo.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

#include <sys/stat.h>
#include <sys/types.h>


int main(void)
{
	if(access(FIFO_NAME,F_OK))	//如果文件不存在
	{
		if(mkfifo(FIFO_NAME,0666)<0)
			perror("mkfifo()");
	}
	else
	{
		unlink(FIFO_NAME);
		perror("unlink()");
		if(mkfifo(FIFO_NAME,0666)<0)
			perror("mkfifo()");
	}
	
	int fd_fifo = open(FIFO_NAME,O_WRONLY);	//只写
	if(fd_fifo < 0)
	{
		perror("open()");
		return -1;
	}
	char msg[20];
	bzero(msg,sizeof(msg));
	
	scanf("%s",msg);
	int num = write(fd_fifo,msg,strlen(msg));
	
	printf("A is write %d bytes msg\n",num);
	
	close(fd_fifo);
	return 0;
}

