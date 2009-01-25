/***************************************************************************
 *            cstrman.h
 *
 *  Fri Apr 14 12:19:05 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#ifndef _CSTRMAN_H
#define _CSTRMAN_H
#include <stdlib.h>
#include <stdio.h>

// - STRING - MANIMPULATION ---------------------------------------------

void UpperCase(char *dest,char *source);
void DeleteSpaceBegEnd (char *str);
int GetStringColumn(char *dest,char *source,char *seperator,int column);
// result:  0 if everything ok
// 			1 column does not exist
// example: 
// GetStringColumn(S,"520::200::234","::",2);
// printf("Number %s",S); // Number 234

// -FILE - OPERATIONS ------------------------------------------------

enum cendl { cwinendl=0,clinendl};

char *cfgets (char *s, int count, FILE *stream);
// same as fgets (without endl charakter)
// for windows and linux txt files

char *cfgets_mem(FILE *stream);
// similar as fgets (without endl charakter)
// for windows and linux txt files
// result: string which must be freed with free(..)
//         NULL if error

int cfgeti (int *number,FILE *stream);
int cfputs (const char *s, FILE *stream, int endl_win_or_lin);
// same as fputs, but puts an endl charakter; //windows or linux
// take cwinendl or clinendl
int cfputi (int number, FILE *stream, int endl_win_or_lin);
#endif /* _CSTRMAN_H */
