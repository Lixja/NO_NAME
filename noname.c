#include <ncurses.h>
#include <unistd.h>

#include "NONAME/nprint.h"
#include "NONAME/nwin.h"
#include "NONAME/ninput.h"
#include "NONAME/forms.h"
#include "NONAME/sh.h"
#include "NONAME/nserver.h"

#define NAME "NO_NAME"

void init_screen(), initW(), run();
NWIN* create_win();

NWIN *nnsh, *nntabs[100];
int position_nt = 0;
int focus = 0; 	//0 = Shell, 1-100 =tabs
int state = 0; //0 = init, 1 = Run


int main(int argc, char* argv[]){
	init_screen();
	create_nserver(create_win);
	//Print some text and waiting for input
	aprint(A_REVERSE,"Loading NO_NAME ...");
	getch();
	clear();
	maprint(A_STANDOUT, NAME, 0, (COLS-(strlen(NAME)))/2);
	refresh();
	initW();
	run();

	clear();
	refresh();
	endwin();
		
	return 0;
}

void initW(){
	nnsh = init(nnsh);
	init_shell(nnsh);
	nnsh->dojob = handle_shell;

	//creating the nwins
	create_nwin(nnsh);
	wbkgd(nnsh->border, COLOR_PAIR(1));
	nbox(nnsh);
}

NWIN* create_win(){
	NWIN *t = nntabs[position_nt];
	t = init(t);
	init_tab(t, 0);
	create_nwin(t);
	wbkgd(nnsh->border, COLOR_PAIR(2));
	nbox(nnsh);
	return t;
}

void run(){
	state = 1;
	run_ninput();
	while(state == 1){
		nrefresh(nnsh);
		for(int i=0; i<position; i++){
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
