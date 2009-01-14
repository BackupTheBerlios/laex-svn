#ifndef _CENTRY_H
#define _CENTRY_H

#include <glib.h>

typedef struct {const char* lang1name; //const
                const char* lang2name; //const
                char* word1;           // momorymenagemanet
                char* word2;           // momorymenagemanet
                char* groupname;       // momorymenagemanet
                unsigned int panel;     //const
                unsigned int days;
                } cENTRY;

cENTRY* centry_new();
void centry_set(cENTRY *entry, const char* lang1name,const char* lang2name, char* word1, char* word2, const char* listname, unsigned int panel, unsigned int days);
void centry_delete(cENTRY *entry);

gboolean centry_groupexist(cENTRY *entry,char *group);
gboolean centry_groupchange(cENTRY *entry,char *oldgroupname,char *newgroupname);
gboolean centry_groupdelete(cENTRY *entry,char *groupname);

#endif /*_CENTRY_H*/
