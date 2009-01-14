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


// STRING - LIST - OPERATIONS ------------------------------------------

typedef struct {int Count; char **strings;} cSTRINGLIST;

void cInitStringList(cSTRINGLIST *list);
// You should call it at the beginning (sets Count=0 and strings=NULL)
void cAddString(cSTRINGLIST *list,char *str);
// Add a string to the list
void cChangeString(cSTRINGLIST *list,int Number,char *str);
void cClearStringList(cSTRINGLIST *list);
// Clear the List and frees the memory (you should call it before quit
void cInsertStringFirst(cSTRINGLIST *list,char *str);
// Insert a string at the beginning (strings[0]) of the list
void cSwapStrings(cSTRINGLIST *list,int Number1, int Number2);
// Swaps Number1 and Number2
int cSearchString(cSTRINGLIST *list,char *str);
// if str is in the list return value is number of array, -1 str is not in the list



// -FILE - OPERATIONS ------------------------------------------------

enum cendl { cwinendl=0,clinendl};

char *cfgets (char *s, int count, FILE *stream);
// same as fgets (without endl charakter)
// for windows and linux txt files
int cfgeti (int *number,FILE *stream);
int cfputs (const char *s, FILE *stream, int endl_win_or_lin);
// same as fputs, but puts an endl charakter; //windows or linux
// take cwinendl or clinendl
int cfputi (int number, FILE *stream, int endl_win_or_lin);
#endif /* _CSTRMAN_H */
