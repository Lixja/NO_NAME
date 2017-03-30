#ifndef NINPUT_H
#define NINPUT_H

#include <ncurses.h>
#include <pthread.h>

#include "nwin.h"
#include "nprint.h"

extern int focus, state;
extern NWIN *nnsh, *nntabs[100];

void *input(){
	NWIN *owin;
	while(state == 1){
		if(focus == 0){
			owin = nnsh;
		}else{
			if(nntabs[focus-1] != NULL){
				owin = nntabs[focus-1];
			}
			
		}

		int c = getch();
		if(c == '\n'){
			nputc(owin, c);
			put_ichar(owin,c);
			if(owin->dojob != NULL){
				owin->dojob(owin->win,owin->input);
				clear_input(owin);
			}
		}else if(c == KEY_F(5)){
			--focus;
		}else if(c == KEY_F(6)){
			++focus;
		}else if(c == KEY_F(3)){
			focus = 3;
		}else if(c == KEY_BACKSPACE){
			nremchar(owin);
			rem_char(owin);
		}else if(c == 27){
			state = 0;
		}else{
			put_ichar(owin, c);
			nputc(owin, c);
		}
	}
}

void run_ninput(){
	pthread_t nin;
	pthread_create(&nin, NULL, input, NULL);
}

#endif