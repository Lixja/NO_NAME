#ifndef NCLIENT_H
#define NCLIENT_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../NONAME/nstring.h"

#define READY "rfn"

typedef struct{
	key_t key;
	int shmflg;
	int size;
	int id;
	char* sstr;
}con;

int timeout = 10;
int alive = 0;
con c, pc;
void *establish_connection(), *handle();
int reply = 0;

char com;
char msg[100];

int connect_to_nnserver(){
	c.key = 36987;
	c.size = 50;

	c.id = shmget(c.key, c.size, IPC_CREAT | 0666);
	c.sstr = shmat(c.id, NULL, 0);

	pthread_t nserver;
	pthread_create(&nserver, NULL, establish_connection, NULL);
}

void *establish_connection(){
	while(strcmp(c.sstr, READY) != 0){
		sleep(1);
	}
	strcpy(c.sstr, "n");
	while(c.sstr[0] == 'n'){
		sleep(1);
	}
	alive =1;
	pc.key = atol(c.sstr);
	pc.size = 100;
	pc.id = shmget(pc.key, pc.size, IPC_CREAT | 0666);
	pc.sstr = shmat(pc.id, NULL, 0);
	strcpy(c.sstr, READY);
	pthread_t nserver;
	pthread_create(&nserver, NULL, handle, NULL);

}

void *handle(){
	while(alive == 1){
		if(com != 0){
			switch(com){
				case 'w':
				strcpy(pc.sstr, nstrcat(&com,msg));
				com = 0;
				break;
			}
		}
		if(strcmp(pc.sstr, READY) == 0){
			reply = 1;
		}
		sleep(1);
	}
}

void wait_for_connecting(){
	while(alive==0 && timeout > 0){
		sleep(1);
		timeout--;
	}
}

void wait_for_reply(){
	while(reply == 0){
		sleep(0);
	}
	reply = 0;
}

void write_msg(char* to_write){
	com = 'w';
	strcpy(msg, to_write);
	wait_for_reply();
}

void close_connection(){
	while(com != 0){
		sleep(1);
	}
}

#endif
