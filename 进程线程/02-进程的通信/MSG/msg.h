#ifndef _MSG_H_
#define _MSG_H_
/* 
 * 消息队列的通讯非常简便，内核为其进行内存分配、检查边界
 * 、设置阻塞以及各种权限监控，因此消息队列的通讯效率不高
 * 不适合海量的数据通讯，只适用于一些进程直接普通的需要数
 * 据识别的通讯
 */


#define MSGSIZE		64

#define PROJ_PATH	"."		//当前路径作为键值
#define PROJ_ID		1

#define J2R			1L		//消息标识
#define R2J			2L

struct msg_buf{				//带标识的结构体
	long type;
	char content[MSGSIZE];
};


#endif
