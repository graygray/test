#to put this makefile at project root

CC = g++
CFLAGS = -ansi -O -Wall
PRJ_PATH = D:\prj\github\test
all: test.o
	${CC} $(CFLAGS) -o x test.o 
test.o: 
	${CC} $(CFLAGS) test.cpp -c
.PHONY : clean 
clean:
	rm -rf *.o *.exe
