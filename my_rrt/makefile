CC=gcc
CFLAGS=-I. 

rrt: rrt.o tools.o 
	$(CC) -o rrt rrt.o tools.o -g -lm

rrt.o: rrt.c tools.h
	gcc -c rrt.c -g -lm

tools.o: tools.c tools.h
	gcc -c tools.c -g -lm


clean:
	rm -r rrt *.o
