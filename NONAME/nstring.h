#ifndef NSTRING_H
#define NSTRING_H

#include <stdlib.h>
#include <string.h>

char* nstrcat(char* str1, char* str2){
	char *res = malloc(strlen(str1) + strlen(str2));
	strcpy(res, str1);
	strcat(res, str2);
}

#endif