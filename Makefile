CC = gcc
CFLAGS=-D_REENTRANT -D_XOPEN_SOURCE=600
LIBS=-lncurses -lpthread
STD=-std=c99

noname:
	$(CC) $(CFLAGS) noname.c -o noname -m32 $(STD) $(LIBS)
clean:
	rm -r noname
