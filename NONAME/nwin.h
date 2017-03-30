#ifndef NWIN_H
#define NWIN_H

#include <ncurses.h>
#include <stdlib.h>

typedef void(*function)(WINDOW *win, char*);

typedef struct{
	WINDOW *border;
	WINDOW *win;
	char input[250];
	int to_update;
	int position;
	int x;
	int y;
	int width;
	int height;
	function dojob;
}NWIN;

NWIN* init(NWIN *nwin){
	nwin = malloc(sizeof *nwin);
	nwin->position =0;
	nwin->to_update = 1;
	return nwin;
}

void create_nwin(NWIN *nwin){
	nwin->border = newwin(nwin->height, nwin->width, nwin->y, nwin->x);
	nwin->win = newwin(nwin->height-1, nwin->width-1, nwin->y+1, nwin->x+1);
}

void put_ichar(NWIN *nwin, char c){
	nwin->input[nwin->position] = c;
	nwin->position++;
}

void rem_char(NWIN *nwin){
	if(nwin->position >0){
		nwin->position--;
		nwin->input[nwin->position] = 0;
	}
}

void nbox(NWIN *nwin){
	box(nwin->border,0,0);
	wrefresh(nwin->border);
}

void nrefresh(NWIN *nwin){
	if(nwin->to_update == 1){
		wrefresh(nwin->win);
		nwin->to_update = 0;
	}
}

void clear_input(NWIN * nwin){
	for(int i=0; i<nwin->position;i++){
		nwin->input[i] = 0;
	}
	nwin->position = 0;
}

#endif