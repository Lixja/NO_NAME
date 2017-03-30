CC = gcc
CFLAGS=-D_REENTRANT -D_XOPEN_SOURCE=600
LIBS=-lpthread
STD=-std=c99

noname:
	$(CC) $(CFLAGS) version.c -o ../bin/version -m32 $(STD) $(LIBS)
clean:
	rm -r ../bin/version
debug:
	$(CC) -g $(CFLAGS) version.c -o ../bin/gversion -m32 $(STD) $(LIBS)