#ifndef FORMS_H
#define FORMS_H

#include "../NWIN/nwin.h"


void init_tab(NWIN *nwin, int pos){
	nwin->y=1;
	nwin->width =(COLS/4);
	nwin->height=((LINES/4)*3)-1;
	nwin->x = (COLS/4)*pos;
}

void init_shell(NWIN *nwin){
	nwin->x=0;
	nwin->y=(LINES/4)*3;
	nwin->width=COLS;
	nwin->height=(LINES/4);
}

#endif