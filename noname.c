#include <ncurses.h>
#include <unistd.h>

#include "NONAME/nprint.h"
#include "NONAME/nwin.h"
#include "NONAME/ninput.h"
#include "NONAME/forms.h"
#include "NONAME/sh.h"
#include "NONAME/nserver.h"

#define NAME "NO_NAME"

void init_screen(), initSH(), run();
NWIN* create_win();

NWIN *nnsh, *nntabs[100];
int position_nt = 0;
int focus = 0; 	//0 = Shell, 1-100 =tabs
int state = 3; //0 = init, 1 = Run, 3=config


int main(int argc, char* argv[]){
	init_screen();
	//Print some text and waiting for input
	aprint(A_REVERSE,"Loading NO_NAME ...");
	getch();
	clear();
	maprint(A_STANDOUT, NAME, 0, (COLS-(strlen(NAME)))/2);
	refresh();
	initSH();
	run();

	clear();
	refresh();
	endwin();
		
	return 0;
}

void initSH(){
	nnsh = init(nnsh);
	init_shell(nnsh);
	nnsh->dojob = handle_shell;

	//creating the nwins
	create_nwin(nnsh);
	wbkgd(nnsh->border, COLOR_PAIR(1));
	nbox(nnsh);
	scrollok(nnsh->win, TRUE);
}

NWIN* create_win(){
	nntabs[position_nt] = init(nntabs[position_nt]);
	init_tab(nntabs[position_nt], 1);
	create_nwin(nntabs[position_nt]);
	wbkgd(nntabs[position_nt]->border, COLOR_PAIR(2));
	nbox(nntabs[position_nt]);
	position_nt++;
	return nntabs[position_nt-1];
}

void run(){
	state = 1;
	create_nserver(create_win);
	run_ninput();
	while(state == 1){
		nrefresh(nnsh);
		for(int i=0; i<position_nt; i++){
			nrefresh(nntabs[i]);
		}
		usleep(500);
	}
}

void init_screen(){
	initscr();
	raw();
	cbreak();
	start_color();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
	init_pair(1,COLOR_GREEN, COLOR_BLACK);
	init_pair(2,COLOR_CYAN, COLOR_BLACK);
	init_pair(3,COLOR_RED, COLOR_BLACK);
}
