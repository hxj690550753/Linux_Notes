all:
	arm-linux-gcc -c main.c -o main.o
	arm-linux-gcc -c test.c -o test.o
	arm-linux-gcc main.o test.o -o main.elf
	arm-linux-objdump -D main.elf > main_inline.dis

clean:
	rm *.o *.elf *.dis
