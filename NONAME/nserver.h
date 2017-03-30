#ifndef NSERVER_H
#define NSERVER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <stdio.h>
#include "nwin.h"
#include "nprint.h"
#include "nstring.h"

#define READY "rfn"

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
	con *c;
}prg;

con c;
extern int state;
prg prgs[100];
int position;

extern NWIN* create_win(); 

void *handle_new(), *handle(void*);

int create_nserver(){
	position = 0;
	c.key = 36987;
	c.size = 50;

	c.id = shmget(c.key, c.size, IPC_CREAT | 0666);
	c.sstr = shmat(c.id, NULL, 0);
	strcpy(c.sstr, READY);

	pthread_t nserver;
	pthread_create(&nserver, NULL, handle_new, NULL);
}

void *handle_new(){
	while(state != 0){
		if(c.sstr[0] == 'n'){
			con pc;
			pc.key = c.key + position +1;
			pc.size = 100;
			pc.id = shmget(pc.key, pc.size, IPC_CREAT | 0666);
			pc.sstr = shmat(pc.id, NULL, 0);
			prg p;
			strcpy(p.name, c.sstr);
			p.alive = 1;
			p.c = &pc;	
			p.win = create_win();
			sprintf(c.sstr, "%d", pc.key);
			while(c.sstr[0] != 'r'){
				usleep(500);
			}
			pthread_t nserver;
			pthread_create(&nserver, NULL, handle, &p);
		}
		usleep(500);
	}
}

void *handle(void* pp){
	prg *p = (prg*) pp;
	while(state == 1 && p->alive == 1){
		if(p->c->sstr[0] == 'w'){
			char msg[100];
			strcpy(msg, p->c->sstr);
			nprint(p->win,nsub(msg, 1));
			strcpy(p->c->sstr, READY);
		}
		usleep(500);
	}
}

#endif
