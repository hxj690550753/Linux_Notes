#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

char dir[20] = "/home/book/work";

int main(void)
{
	DIR *dp = opendir(dir);		//获取目录
	struct dirent *ep = NULL;	//目录项指针
	while(NULL != (ep=readdir(dp)))
	{
		printf("d_name:%s\t\td_reclen:%u\t\td_type:%c\n",ep->d_name,ep->d_reclen,ep->d_type);
	}
	closedir(dp);
	dp = NULL;
	ep = NULL;
	return 0;
}