#ifndef NPRINT_H
#define NPRINT_H

#include <ncurses.h>
#include "nwin.h"

void cprint(int i, char* str){
	attron(COLOR_PAIR(i));
	printw(str);
	attroff(COLOR_PAIR(i));
}

void aprint(int i, char* str){
	attron(i);
	printw(str);
	attroff(i);
}

void maprint(int i, char* str,int x,int y){
	attron(i);
	mvprintw(x,y,str);
}

void cprintw(NWIN *nwin, int i, char* str){
	attron(COLOR_PAIR(i));
	wprintw(nwin->win, str);
	attroff(COLOR_PAIR(i));
}

void nprint(NWIN *nwin, char* str){
	wprintw(nwin->win, str);
	nwin->to_update = 1;
}

void nputc(NWIN *nwin, char c){
	waddch(nwin->win, c);
	nwin->to_update=1;
}
void nremchar(NWIN* nwin){
	int x = getcurx(nwin->win);
	int y = getcury(nwin->win);
	x--;
	if(x>=0){
		wmove(nwin->win, y,x);
		wdelch(nwin->win);
		nwin->to_update=1;
	}
}

#endif