CC=g++
CFLAGS=-c -Wall -g

mips : mips.o
	$(CC) mips.o -o mips
mips.o : mips.cpp Anti_assembler.h Anti_assembler.cpp
	$(CC) mips.cpp  $(CFLAGS) -o mips.o
clean :
	del *.o *.exe