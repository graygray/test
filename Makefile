#to put this makefile at project root

CC = g++
CFLAGS = -ansi -O -Wall -std=c++11
LDFLAGS = -lpthread

PRJ_PATH = D:\prj\github\test

all: test.o lib_crc.o
	${CC} $(CFLAGS) -o x test.o lib_crc.o $(LDFLAGS)
test.o: 
	${CC} $(CFLAGS) test.cpp -c
lib_crc.o: 
	${CC} $(CFLAGS) lib_crc.c -c
.PHONY : clean 
clean:
	rm -rf *.o *.exe
