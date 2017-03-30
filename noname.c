#include <ncurses.h>
#include <unistd.h>

#include "NWIN/nprint.h"
#include "NWIN/nwin.h"
#include "NWIN/ninput.h"
#include "NONAME/forms.h"
#include "NONAME/sh.h"

#define NAME "NO_NAME"

void init_screen(), initW(), run();

NWIN *nntab, *nnwin, *nnside, *nnsh;
int focus = 3; 	//0 = Tab, 1=Win, 2=Side, 3 = Shell
int state = 0; //0 = init, 1 = Run


int main(int argc, char* argv[]){
	init_screen();

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
	nntab = init(nntab);
	nnwin = init(nnwin);
	nnside = init(nnside);
	nnsh = init(nnsh);

	init_tab(nntab, 0);
	init_tab(nnwin, 1);
	init_tab(nnside, 3);
	init_shell(nnsh);
	nnsh->dojob = handle_shell;

	//creating the nwins
	create_nwin(nntab);
	create_nwin(nnwin);
	create_nwin(nnside);
	create_nwin(nnsh);
	wbkgd(nntab->border, COLOR_PAIR(2));
	wbkgd(nnwin->border, COLOR_PAIR(3));
	wbkgd(nnside->border, COLOR_PAIR(2));
	wbkgd(nnsh->border, COLOR_PAIR(1));
	nbox(nntab);
	nbox(nnwin);
	nbox(nnside);
	nbox(nnsh);
}

void run(){
	state = 1;
	run_ninput();
	while(state == 1){
		nrefresh(nntab);
		nrefresh(nnsh);
		nrefresh(nnside);
		nrefresh(nnwin);
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
