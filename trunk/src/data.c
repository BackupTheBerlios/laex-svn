#include "data.h"
#include "string.h"
#include "cstrman.h"

cDATA user_data;

void cdata_init()
{
    user_data.dictfile=NULL;
	user_data.grouplist=NULL;
	user_data.cwordlist=NULL;
    user_data.trainlist=NULL;
	user_data.trainindex=0;
	user_data.traingroup=0;
	user_data.trainasked=FALSE;
	user_data.main_window_ui=0;
	user_data.dialog_edit_entry_ui=NULL;
	user_data.dialog_edit_entry_ui=NULL;
	user_data.dialog_start_training_ui=NULL;
	user_data.traindirection=FALSE;
	user_data.lang1name="German";
	user_data.lang2name="English";
	
    user_data.dictfile = (char*)malloc(strlen("de-en.txt"));
    strcpy(user_data.dictfile,"de-en.txt");
    user_data.cwordlist = g_array_new(TRUE,FALSE,sizeof(cENTRY*));
    user_data.grouplist = g_array_new(TRUE,FALSE,sizeof(char*));
    cdata_loaddicfile();
}

void cdata_loaddicfile()
{
    FILE *f;
    char S[1000], lang1[1000],lang2[1000];
    char *S2;
    cENTRY *entry;
    S2 = (char*) malloc(strlen(_("Stadt"))+1);
    strcpy(S2,_("Stadt"));
    g_array_append_val(user_data.grouplist,S2);
    S2 = (char*) malloc(strlen(_("Land"))+1);
    strcpy(S2,_("Land"));
    g_array_append_val(user_data.grouplist,S2);
    S2 = (char*) malloc(strlen(_("Fluss"))+1);
    strcpy(S2,_("Fluss"));
    g_array_append_val(user_data.grouplist,S2);
    f = fopen(user_data.dictfile,"r");
    if (f==NULL) return;
    while (feof(f) == 0)
    	{
	       entry = centry_new();
           cfgets(S, 1000, f);
	       if (S[0]=='#') continue;
           if (GetStringColumn(lang1,S,"::",0)!=0) continue;
	       if (GetStringColumn(lang2,S,"::",1)!=0) continue;
	       centry_set(entry, "Deutsch","Englisch", lang1, lang2, "", 0,0);
	       g_array_append_val(user_data.cwordlist,entry);
        }
    fclose(f);
    entry = g_array_index (user_data.cwordlist, cENTRY*, 1);
}

cDATA *cdata_get()
{
    return &user_data;
}

void cdata_delete()
{
    int i;
    free(user_data.dictfile);
    for (i=0;i!=(int)user_data.cwordlist->len;i++)
      {
          centry_delete(g_array_index (user_data.cwordlist, cENTRY*, i));
      }
    g_array_free(user_data.cwordlist,TRUE);
    for (i=0;i!=(int)user_data.grouplist->len;i++)
      {
         free(g_array_index (user_data.grouplist, char*, i));
       }
    g_array_free(user_data.grouplist,TRUE);
}
