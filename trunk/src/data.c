#include "data.h"
#include "string.h"
#include "cstrman.h"
#include <libxml/tree.h>

cDATA user_data;

cDATA* cdata_init()
{
        cDATA* data;
        data = (cDATA*)malloc(sizeof(cDATA));
        data->dictfile=NULL;
	data->grouplist=NULL;
	data->cwordlist=NULL;
        data->trainlist=NULL;
	data->trainindex=0;
	data->traingroup=0;
	data->trainasked=FALSE;
	data->main_window_ui=0;
	data->dialog_edit_entry_ui=NULL;
	data->dialog_edit_entry_ui=NULL;
	data->dialog_start_training_ui=NULL;
	data->traindirection=FALSE;
	data->lang1name="German";
	data->lang2name="English";
	data->paneldays[0]=0;
	data->paneldays[1]=0;
	data->paneldays[2]=3;
	data->paneldays[3]=7;
	data->paneldays[4]=14;
	
        data->dictfile = (char*)malloc(strlen("de-en.txt"));
        strcpy(data->dictfile,"de-en.txt");
        data->cwordlist = g_array_new(TRUE,FALSE,sizeof(cENTRY*));
        data->grouplist = g_array_new(TRUE,FALSE,sizeof(char*));
        cdata_loaddicfile(data);
        return data;
}

void cdata_loaddicfile(cDATA *data)
{
    FILE *f;
    char S[2000], lang1[2000],lang2[2000],la1[2000],la2[2000],group[2000],panels[2000],dayss[2000];
    cENTRY *entry;
    int i;
    f = fopen("dic.laex","r");
    //f = fopen(data->dictfile,"r");
    if (f==NULL) return;
    //cdata_addgrouptolist(data,"");
    i=0;
    while (1)
    	{
	       entry = centry_new();
           cfgets(S, 2000, f);
           if (feof(f) != 0) break;
	       if (S[0]=='#') continue;i++;
           if (GetStringColumn(lang1,S,"::",0)!=0) continue;
	   if (GetStringColumn(lang2,S,"::",1)!=0) continue;
	   if (GetStringColumn(la1,S,"::",2)!=0) {sprintf(la1,"German");};
	   if (GetStringColumn(la2,S,"::",3)!=0) {sprintf(la2,"English");};
	   if (GetStringColumn(group,S,"::",4)!=0) {sprintf(group,"");};
	   if (GetStringColumn(panels,S,"::",5)!=0) {sprintf(panels,"0");};
	   if (GetStringColumn(dayss,S,"::",6)!=0) {sprintf(dayss,"0");};
	   centry_set(entry, la1,la2, lang1, lang2, group, atoi(panels),atoi(dayss));
	   cdata_addgrouptolist(data,group);
	   if (strstr(group,"0")!=0) g_print("Error in line %d\n",i);
	   g_array_append_val(data->cwordlist,entry);
        }
    fclose(f);
}

void cdata_savedicfile(cDATA *data)
{
    FILE *f;
    cENTRY *entry;
    int i;
    f = fopen("dic.laex","w");
    if (f==NULL) return;
     
  for (i=0;i!=data->cwordlist->len;i++)
    {
       entry=g_array_index (data->cwordlist, cENTRY*, i);
       fprintf(f,"%s::",entry->word1);
       fprintf(f,"%s::",entry->word2);
       fprintf(f,"%s::",entry->lang1name);
       fprintf(f,"%s::",entry->lang2name);
       fprintf(f,"%s::",entry->groupname);
       fprintf(f,"%d::",entry->panel);
       fprintf(f,"%d\n",entry->days);
    }
    fclose(f);
}



void cdata_delete(cDATA *data)
{
    int i;
    cdata_savedicfile(data);
    free(data->dictfile);
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
          centry_delete(g_array_index (data->cwordlist, cENTRY*, i));
      }
    g_array_free(data->cwordlist,TRUE);
    for (i=0;i!=(int)data->grouplist->len;i++)
      {
         free(g_array_index (data->grouplist, char*, i));
       }
    g_array_free(data->grouplist,TRUE);
    free(data);
    data=NULL;
}
void cdata_addgrouptolist(cDATA *data,char *group)
{
    char *S,*S2,*S3;
    int i,i2;
    if (group==NULL) return;
    if (strcmp(group,"")==0) return;
    if (strcmp(group," ")==0) return;
    gboolean inside;
    S = (char *)malloc(strlen(group)+1);
    i=0;
    while (1)
     {
         if (GetStringColumn(S,(char *)group,"|",i)==1) break;
          inside=FALSE;
          for (i2=0;i2!=data->grouplist->len;i2++)
            {
               S2=g_array_index (data->grouplist, char*, i2);
               if (strcmp(S,S2)==0)
                 {
                   inside=TRUE;
                   break;
                 }
            }
          if (inside==FALSE)
            {
               S3=(char *)malloc(strlen(S)+1);
               strcpy(S3,S);
               g_array_append_val(data->grouplist,S3);
            }
         i++;
     }
    free(S);
}

void cdata_saveXMLWordList(cDATA *data, char *filename)
{
  xmlDoc *doc;
  xmlNodePtr rootNode,entryNode;
  int i;
  cENTRY *entry;
  char S[10000];
  
  doc = xmlNewDoc ((const xmlChar *)"1.0");
  rootNode = xmlNewNode (NULL, (const xmlChar *)"Laex");
  xmlDocSetRootElement (doc, rootNode);
  
  for (i=0;i!=data->cwordlist->len;i++)
    {
       entry=g_array_index (data->cwordlist, cENTRY*, i);
       entryNode = xmlNewNode (NULL, (const xmlChar *)"Entry");
       xmlAddChild (rootNode, entryNode);
       xmlSetProp(entryNode,(const xmlChar *)"Language_1_Name",(const xmlChar *)entry->lang1name);
       xmlSetProp(entryNode,(const xmlChar *)"Language_2_Name",(const xmlChar *)entry->lang2name);
       xmlSetProp(entryNode,(const xmlChar *)"Word_Language_1",(const xmlChar *)entry->word1);
       xmlSetProp(entryNode,(const xmlChar *)"Word_Language_2",(const xmlChar *)entry->word2);
       xmlSetProp(entryNode,(const xmlChar *)"Group",(const xmlChar *)entry->groupname);
       sprintf(S,"%d",entry->panel);
       xmlSetProp(entryNode,(const xmlChar *)"Panel",(const xmlChar *)S);
       sprintf(S,"%d",entry->days);
       xmlSetProp(entryNode,(const xmlChar *)"Days",(const xmlChar *)S);
    }
  
  
  xmlSaveFile (filename, doc);
  xmlFreeDoc (doc); 
}
