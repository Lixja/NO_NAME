CC = gcc
CFLAGS=-D_REENTRANT -D_XOPEN_SOURCE=600
LIBS=-lncurses -lpthread
STD=-std=c99

all: noname apps
noname:
	$(CC) $(CFLAGS) noname.c -o noname $(STD) $(LIBS)
clean:
	rm -r noname
apps:
	cd NNAPPS && $(MAKE) all
debug:
	$(CC) $(CFLAGS) -g noname.c -o dnoname $(STD) $(LIBS)
