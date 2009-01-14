/***************************************************************************
 *            cstrman.c
 *
 *  Fri Apr 14 12:18:47 2006
 *  Copyright  2006  User
 *  Email
 ****************************************************************************/

#include "cstrman.h"
#include <string.h>
#include <stdlib.h>

void UpperCase(char *dest,char *source)
{
	int i;
	for (i=0;i!=(int)strlen(source)+1;i++)
		{
		  if ((source[i] >= 'a') && (source[i] <= 'z'))
		  	{
			  dest[i]=source[i]-'a'+'A';
			} else
		    {
			  unsigned char ch;
			  ch = source[i];
			  switch (ch)
			  {
				case 164 : dest[i]=132;break; //ä=195,164; Ä=195,132
				case 188 : dest[i]=156;break; //ü=195,188; Ü=195,156
				case 182 : dest[i]=150;break; //ö=195,182; Ö=195,150
				  default: dest[i]=source[i];
			  }
			}
		
		}
}

void DeleteSpaceBegEnd (char *str)
{
  while (str[0]==' ')
  	{
		strcpy(str,&(str[1]));
	}
  while (str[strlen(str)-1]==' ')
  	{
		str[strlen(str)-1]=0;
	}
}

int GetStringColumn(char *dest,char *source,char *seperator,int column)
{
  char *pos;
  char *oldpos;
  pos=source-strlen(seperator);;
  oldpos=pos;
  int i;
  for (i=0;i!=column+1;i++)
  	{
  		oldpos=pos+strlen(seperator);
		pos = strstr(oldpos, seperator);
  			if (pos==NULL) 
  			{
	  			if (column==i)
  					{
	  					strncpy(dest, oldpos,strlen(oldpos));
						dest[strlen(oldpos)]=0;
	  					return 0;
					} else
					{
		    			dest=NULL;
		    			return 1;
					}
			}
		
	 }
	 strncpy(dest,oldpos,(int)(pos-oldpos));
	 dest[(int)(pos-oldpos)]=0;
  return 0;
}

void cInitStringList(cSTRINGLIST *list)
{
list->Count=0;
list->strings=NULL;
}

void cAddString(cSTRINGLIST *list,char *str)
{
  list->Count++;
  list->strings=(char **)realloc ((char *)(list->strings), list->Count*sizeof(char *));
  list->strings[list->Count-1]=(char *)malloc(strlen(str)+1);
  strcpy(list->strings[list->Count-1],str);
}

void cChangeString(cSTRINGLIST *list,int Number,char *str)
{
  free(list->strings[Number]);
  list->strings[Number]=(char*)malloc(strlen(str)+1);
  strcpy(list->strings[Number],str);
}

void cClearStringList(cSTRINGLIST *list)
{
  if (list->Count==0) return;
  int i;
  for (i=0;i!=list->Count;i++)
  	{
	  free(list->strings[i]);
	}
  free(list->strings);
  list->strings=NULL;
  list->Count=0;	
}

void cInsertStringFirst(cSTRINGLIST *list,char *str)
{
  cAddString(list,str);
  if (list->Count==1) return;
  char *S=list->strings[list->Count-1];
  int i;
  for (i=list->Count-1;i!=0;i--)
  	{
	  list->strings[i]=list->strings[i-1];
	}
  list->strings[0]=S;
}

void cSwapStrings(cSTRINGLIST *list,int Number1, int Number2)
{
  if ((Number1 < 0) || (Number1 >= list->Count)) return; 
  if ((Number2 < 0) || (Number2 >= list->Count)) return;
  char *S;
  S=list->strings[Number1];
  list->strings[Number1]=list->strings[Number2];
  list->strings[Number2]=S;
}

int cSearchString(cSTRINGLIST *list,char *str)
{
 int i,result;
 if (list->Count==0) return -1;
 result=-1;
 for (i=0;i!=list->Count;i++)
 	{
	  if (strcmp(list->strings[i],str)==0)
	  	{
		  result=i;
		  break;
		}
	}
 return result;
}

char *cfgets (char *s, int count, FILE *stream)
{
  if (s==NULL) return NULL;
  int ready;
  int i;
  ready=0;
  i=0;
  char ch;
  while (ready==0)
    {
	  ch=fgetc(stream);
	  if ((ch==EOF) && (i==0)) {s=NULL;return 0;}
	  if (i>=count-2) ready=1;
      if (ch==13) 
		 {i--;} else
	  if (ch==10)
	  	 {ready=1;} else
	  if (ch==EOF)
	  	 {ready=1;} else
	     {s[i]=ch;}	 
	  i++;
	}
   s[i-1]=0;
  return s;
}

int cfgeti (int *number,FILE *stream)
{
char S[128];
cfgets (S,128,stream);
if (S==NULL) return -1;
*number = atoi(S);
return 0;
}

int cfputs (const char *s, FILE *stream, int endl_win_or_lin)
{
 if (s==NULL) return 0;
 char *s2;
 int result;
 s2=(char *)malloc(strlen(s)+3);
 strcpy(s2,s);
 if (endl_win_or_lin==cwinendl)
 	{
	  s2[strlen(s)]=13;
	  s2[strlen(s)+1]=10;
	  s2[strlen(s)+2]=0;
	} else
    {
	  s2[strlen(s)]=10;
	  s2[strlen(s)+1]=0;
	}
 
  result = fputs(s2,stream);
 free(s2);
 return result;
}

int cfputi (int number, FILE *stream, int endl_win_or_lin)
{
 char S[128];
 sprintf(S,"%d",number);
 return cfputs(S,stream,endl_win_or_lin);
}
