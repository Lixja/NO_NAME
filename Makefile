CC = gcc
CFLAGS=-D_REENTRANT
LIBS=-lncurses -lpthread
STD=-std=c99

noname:
	$(CC) $(CFLAGS) noname.c -o noname $(STD) $(LIBS)
clean:
	rm -r noname
