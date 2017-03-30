CC = gcc
CFLAGS=-D_REENTRANT -D_XOPEN_SOURCE=600
LIBS=-lpthread
STD=-std=c99

all: version date echo helloworld
	
version:
	$(CC) $(CFLAGS) version.c -o ../bin/version -m32 $(STD) $(LIBS)
date:
	$(CC) $(CFLAGS) date.c -o ../bin/date -m32 $(STD) $(LIBS)
echo:
	$(CC) $(CFLAGS) echo.c -o ../bin/echo -m32 $(STD) $(LIBS)
helloworld:
	$(CC) $(CFLAGS) helloworld.c -o ../bin/helloworld -m32 $(STD) $(LIBS)
clean:
	rm -r ../bin/*
debug:
	$(CC) -g $(CFLAGS) version.c -o ../bin/gversion -m32 $(STD) $(LIBS)