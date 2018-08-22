#ifndef _SHARE_MEMORY_H_
#define _SHARE_MEMORY_H_

/*
 * 共享内存SHM是把一块毫无保护的内存裸露在进程面前，没有
 * 经过Linux内核的任何操作，读写效率非常高，但是由于没有
 * 任何保护措施，因此必须小心地使用，一般而言配合信号量、
 * 互斥锁一起使用，以免数据被践踏
 */

#define SHMSIZE		1024

#define PROJ_PATH	"."
#define PROJ_ID		100


#endif

