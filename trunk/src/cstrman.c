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

char *cfgets_mem(FILE *stream)
{
  char *S; //memBuffer
  char *S2;
  unsigned int lenS;//reserved Memory
  unsigned int lenSCount;// depends of charakters
  unsigned int stdlenS;//momemory allocation buffer size
  int ready;
  int i;
  char ch;
  
  stdlenS=128;
  lenS=stdlenS;
  S=(char*)malloc(lenS);
  //lenSCount=0;
  ready=0;
  i=0;
  ch=0;
  
  while (ready==0)
    {
	  ch=fgetc(stream);
	  if ((ch==EOF) && (i==0)) 
	                {
	                    free(S);
	                    S=NULL;
                            return NULL;
                        }
	  if (i>=lenS-2) 
	                { 
                            lenS+=stdlenS;
                            S=(char*)realloc(S,lenS);
                            if (S==NULL) 
                                {
                                  return NULL;
                                }
	                }
      if (ch==13) 
		 {i--;} else
	  if (ch==10)
	  	 {ready=1;} else
	  if (ch==EOF)
	  	 {ready=1;} else
	     {S[i]=ch;}	 
	  i++;
	}
   S[i-1]=0;
   S2=(char*)malloc(strlen(S)+1);
   strcpy(S2,S);
   free(S);
  return S2;
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
