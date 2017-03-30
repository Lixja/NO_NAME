#ifndef NCLIENT_H
#define NCLIENT_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

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
con c;
void *establish_connection(), *handle();

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
	strcpy(c.sstr, "nTEST");
	while(c.sstr[0] == 'n'){
		sleep(1);
	}
	alive =1;
	con pc;
	pc.key = atoi(*c.sstr);
	pc.size = 100;
	pc.id = shmget(c.key, c.size, IPC_CREAT | 0666);
	pthread_t nserver;
	pthread_create(&nserver, NULL, handle, NULL);

}

void *handle(){

}

void wait_for_connecting(){
	while(alive==0 && timeout > 0){
		sleep(1);
		timeout--;
	}
}

#endif