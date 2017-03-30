#ifndef SH_H
#define SH_H

#include <ncurses.h>
#include <unistd.h>
#include "../NWIN/nwin.h"
#include "../NWIN/nprint.h"
#include "../NC/nstring.h"

char help[] = "help";
char network[] = "net";

void create_ARGC_ARGV();

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
	}else{
		wprintw(win, "Program not found\n");
	}
	wrefresh(win);
}


#endif