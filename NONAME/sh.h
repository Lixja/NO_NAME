#ifndef SH_H
#define SH_H

#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include "nwin.h"
#include "nprint.h"
#include "nstring.h"

void *execute_prg(void*);

void handle_shell(WINDOW *win, char* input){
	int argc = 0;
	char argv[10][50];
	
	
	char *ptr;
	
	ptr = strtok(input, " \n");
	while(ptr != NULL) {
		strcpy(argv[argc], ptr);
		argc++;
 		ptr = strtok(NULL, " \n");
 	}

	if(access(nstrcat("bin/",argv[0]), X_OK) != -1){
		wprintw(win, nstrcat(argv[0], " will be executed now.\n"));
		pthread_t nin;
		pthread_create(&nin, NULL, execute_prg, nstrcat("bin/",input));

	}else{
		wprintw(win, "Program not found\n");
	}
	wrefresh(win);
}

void *execute_prg(void* cp){
	char *command = (char*) cp;
	system(command);
}


#endif