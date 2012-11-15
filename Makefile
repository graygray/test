#to put this makefile at project root

CC = g++
CFLAGS = -g -ansi -O -Wall
PRJ_PATH = D:\prj\github\test

all:
	${CC} $(CFLAGS) test $(PRJ_PATH)\test.cpp

clean:
	rm -rf *.o *.exe