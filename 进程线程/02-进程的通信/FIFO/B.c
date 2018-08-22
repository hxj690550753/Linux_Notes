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
		perror("access()");
	}
	
	int fd_fifo = open(FIFO_NAME,O_RDONLY);	//只读
	if(fd_fifo < 0)
	{
		perror("open()");
		return -1;
	}
	char msg[20];
	bzero(msg,sizeof(msg));
	
	int num = read(fd_fifo,msg,sizeof(msg));
	
	printf("B is read %d bytes msg:%s\n",num,msg);
	
	close(fd_fifo);
	return 0;
}

