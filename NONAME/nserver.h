#ifndef NSERVER_H
#define NSERVER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include "nwin.h"
#include "nprint.h"

typedef struct{
	key_t key;
	int shmflg;
	int size;
	int id;
	char* sstr;
}con;

typedef struct{
	char name[50];
	int alive;
	NWIN *win;
	con c;
}prg;

con c;
extern int state;
prg prgs[100];
int position;
char *sstr;

extern NWIN* create_win(); 

void *handle_new(), *handle(void*);

int create_nserver(){
	position = 0;
	c.key = 36987;
	c.size = 50;

	c.id = shmget(c.key, c.size, IPC_CREAT | 0666);
	c.sstr = shmat(c.id, NULL, 0);

	pthread_t nserver;
	pthread_create(&nserver, NULL, handle_new, NULL);
}

void *handle_new(){
	while(state == 1){
		if(c.sstr[0] == 'n'){
			con pc;
			pc.key = c.key + position +1;
			pc.size = 100;
			pc.id = shmget(c.key, c.size, IPC_CREAT | 0666);
			prg p;
			strcpy(p.name, c.sstr);
			p.alive = 1;
			p.c = pc;		
			create_win();
			pthread_t nserver;
			pthread_create(&nserver, NULL, handle, &p);	
		}
		sleep(1);
	}
}

void *handle(void* pp){
	prg *p = (prg*) pp;
	while(state == 1 && p->alive == 1){

	}
}

#endif