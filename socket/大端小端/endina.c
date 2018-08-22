#include <stdio.h>

/*
 * 共用体，存放顺序如下，左高地址，右低地址
 * int 	|x|x|x|x|
 * char		  |x|
 */
typedef union ENDIAN_MODEL{
	int i_data;
	char c_data;
}endian_model;


int main(void)
{
	endian_model model;
	model.i_data = 0x12345678;
	printf("int_data  =%8x\n",model.i_data);
	printf("char_data =%8x\n",model.c_data);
	if(model.c_data == 0x12)
		printf("Big-Endian\n");
	if(model.c_data == 0x78)
		printf("Little-Endian\n");
	
	return 0;
}