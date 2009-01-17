#include "centry.h"
#include <string.h>
#include <stdlib.h>
#include "cstrman.h"
char NULLSTR[2];

cENTRY* centry_new()
{
     cENTRY *entry;
     entry = (cENTRY *)malloc(sizeof(cENTRY));
     strcpy(NULLSTR,"");
     entry->lang1name=NULLSTR;
     entry->lang2name=NULLSTR;
     entry->word1=NULLSTR;
     entry->word2=NULLSTR;
     entry->groupname=NULLSTR;
     entry->panel=0;
     entry->days=0;
     return entry;
}

void centry_set(cENTRY *entry, char* lang1name,char* lang2name, char* word1, char* word2, char* listname, unsigned int panel, unsigned int days)
{
  strcpy(NULLSTR,"");
  entry->lang1name=(char*)malloc(strlen(lang1name)+1);
  strcpy(entry->lang1name,lang1name);
  entry->lang2name=(char*)malloc(strlen(lang2name)+1);
  strcpy(entry->lang2name,lang2name);
  entry->word1 = (char*)malloc(strlen(word1)+1);
  strcpy(entry->word1,word1);
  entry->word2 = (char*)malloc(strlen(word2)+1);
  strcpy(entry->word2,word2);
  entry->groupname = (char*)malloc(strlen(listname)+1);
  strcpy(entry->groupname,listname);
  entry->panel=panel;
  entry->days=days;
}

void centry_delete(cENTRY *entry)
{
  free(entry->lang1name);
  free(entry->lang2name);
  free(entry->word1);
  free(entry->word2);
  free(entry->groupname);
  free(entry);
  entry=NULL;
}

gboolean centry_groupexist(cENTRY *entry,char *group)
{
    char *S;
    int i;
    gboolean result;
    S = (char *)malloc(strlen(entry->groupname)+1);
    i=0;
    result = FALSE;
    while (1)
     {
         if (GetStringColumn(S,(char *)entry->groupname,"|",i)==1) break;
         if (strcmp(S,group)==0)
            {
               result = TRUE;
               break;
            }
         i++;
     }
    free(S);
    return result;
}

gboolean centry_groupchange(cENTRY *entry,char *oldgroupname,char *newgroupname)
{
    char *S, *Sges;
    int i;
    gboolean result;
    S = (char *)malloc(strlen(entry->groupname)+1);
    Sges=NULL;
    i=0;
    result = FALSE;
    while (1)
     {
         if (GetStringColumn(S,(char *)entry->groupname,"|",i)==1) break;
         if (strcmp(S,oldgroupname)==0)
            {
               result = TRUE;
               if (Sges==NULL)
                   {
                      Sges=(char*)malloc(strlen(newgroupname)+1);
                      sprintf(Sges,"%s",newgroupname);
                    } else
                    {
                       Sges=(char*)realloc(Sges,strlen(Sges)+strlen(newgroupname)+2);
                       sprintf(Sges,"%s|%s",Sges,newgroupname);
                    }
               break;
            } else
            {
               if (Sges==NULL)
                   {
                      Sges=(char*)malloc(strlen(S)+1);
                      sprintf(Sges,"%s",S);
                    } else
                    {
                      Sges=(char*)realloc(Sges,strlen(Sges)+strlen(S)+2);
                      sprintf(Sges,"%s|%s",Sges,S);
                    }
            }
         i++;
     }
    free(S);
    if (Sges!=NULL) 
       {
        if (result==TRUE)
          {
            free((void*)entry->groupname);
            entry->groupname=Sges;
          } else
          {
            free(Sges);
          }
        }
    return result;
}

gboolean centry_groupdelete(cENTRY *entry,char *groupname)
{
    char *S, *Sges;
    int i;
    gboolean result;
    S = (char *)malloc(strlen(entry->groupname)+1);
    Sges=NULL;
    i=0;
    result = FALSE;
    while (1)
     {
         if (GetStringColumn(S,(char *)entry->groupname,"|",i)==1) break;
         if (strcmp(S,groupname)==0)
            {
               result = TRUE;
            } else
            {
               if (Sges==NULL)
                   {
                      Sges=(char*)malloc(strlen(S)+1);
                      sprintf(Sges,"%s",S);
                    } else
                    {
                      Sges=(char*)realloc(Sges,strlen(Sges)+strlen(S)+2);
                      sprintf(Sges,"%s|%s",Sges,S);
                    }
            }
         i++;
     }
    free(S);
    if (Sges!=NULL)
       {
        if (result==TRUE)
          {
            free((void*)entry->groupname);
            entry->groupname=Sges;
            g_print("%s\n",Sges);
          } else
          {
            free(Sges);
          }
        } else
        {
           if (result==TRUE)
           {
             strcpy(NULLSTR,"");
             free((void*)entry->groupname);
             entry->groupname=NULLSTR;
           }
        }
    return result;
}
