#ifndef NINPUT_H
#define NINPUT_H

#include <ncurses.h>
#include <pthread.h>

#include "nwin.h"
#include "nprint.h"

extern int focus, state;
extern NWIN *nntab, *nnwin, *nnside, *nnsh;

void *input(){
	NWIN *owin;
	while(state == 1){
		if(focus == 0){
			owin = nntab;
		}else if(focus == 1){
			owin = nnwin;
		}else if(focus == 2){
			owin = nnside;
		}else if(focus == 3){
			owin = nnsh;
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
			nremchar(owin);
			focus = 0;
		}else if(c == KEY_F(6)){
			nremchar(owin);
			focus = 1;
		}else if(c == KEY_F(7)){
			nremchar(owin);
			focus = 2;
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