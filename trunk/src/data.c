#include "data.h"
#include "string.h"
#include "cstrman.h"
#include <sys/stat.h>

//#include <libxml/tree.h>

cDATA user_data;

cDATA* cdata_init()
{
        cDATA* data;
        data = (cDATA*)malloc(sizeof(cDATA));
        const gchar *homedir;
        data->dictfile=NULL;
        data->configdir=NULL;
	data->grouplist=NULL;
	data->cwordlist=NULL;
        data->trainlist=NULL;
	data->trainindex=0;
	data->traingroup=0;
	data->trainasked=FALSE;
	data->main_window_ui=0;
	data->dialog_edit_entry_ui=NULL;
	data->dialog_start_training_ui=NULL;
	data->assistant_import_ui=NULL;
	data->assistant_export_ui=NULL;
	data->traindirection=FALSE;
	data->lang1name="German";
	data->lang2name="English";
	data->paneldays[0]=0;
	data->paneldays[1]=0;
	data->paneldays[2]=3;
	data->paneldays[3]=7;
	data->paneldays[4]=14;
	
	// Load Dic File:
	homedir = g_getenv ("HOME");
        if (!homedir) 
           {
             homedir = g_get_home_dir ();
           }
        data->configdir= (char*)malloc(strlen("/.laex")+strlen(homedir)+1);      
        sprintf(data->configdir,"%s/.laex",homedir);
        g_mkdir_with_parents(data->configdir,S_IRUSR | S_IWUSR | S_IXUSR);
	
        data->dictfile = (char*)malloc(strlen("/dic.laex")+strlen(data->configdir)+1);
        sprintf(data->dictfile,"%s/dic.laex",data->configdir);
        data->cwordlist = g_array_new(TRUE,FALSE,sizeof(cENTRY*));
        data->grouplist = g_array_new(TRUE,FALSE,sizeof(char*));
        cdata_loaddicfile(data,data->dictfile,NULL,NULL,NULL,FALSE);
        return data;
}


void cdata_loaddicfile(cDATA *data,char *filename, char *_lang1, char *_lang2, char* _group, gboolean _append){
    FILE *f;
    char *S, *lang1,*lang2,*la1,*la2,*group,*panels,*dayss;
    cENTRY *entry;
    int i;
    
    S=NULL;lang1=NULL;lang2=NULL;la1=NULL;la2=NULL;group=NULL;panels=NULL;dayss=NULL;
    
    if (_append==TRUE)
      {
        // -to do
      } else
      {
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
        data->cwordlist = g_array_new(TRUE,FALSE,sizeof(cENTRY*));
        data->grouplist = g_array_new(TRUE,FALSE,sizeof(char*));
      }
    
    f = fopen(filename,"r");
    if (f==NULL) return;
    while (1)
    	{
	   entry = centry_new();
           S=cfgets_mem(f); // read one line
           if (feof(f) != 0) 
                             { 
                               if (S!=NULL) free(S);
                               S=NULL;
                               break;
                             }
           if (S==NULL)      {
                               continue;
                               break;
                             }
	   if (S[0]=='#')    {
	                       free(S);
                               S=NULL;
	                       continue;
	                     }
           lang1 = (char*)malloc(strlen(S)+1);
           lang2 = (char*)malloc(strlen(S)+1);
           la1 = (char*)malloc(strlen(S)+1);
           la2 = (char*)malloc(strlen(S)+1);
           group = (char*)malloc(strlen(S)+1);
           panels = (char*)malloc(strlen(S)+1);
           dayss = (char*)malloc(strlen(S)+1);
           if (GetStringColumn(lang1,S,"::",0)!=0) 
                                   {
                                     free(lang1);
                                     lang1=NULL;
                                     continue;
                                   }
           DeleteSpaceBegEnd (lang1);
	   if (GetStringColumn(lang2,S,"::",1)!=0) 
	                          {
                                     free(lang2);
                                     lang1=NULL;
                                     continue;
                                   }
	   DeleteSpaceBegEnd (lang2);
	   if (GetStringColumn(la1,S,"::",2)!=0) 
	                           {
	                              if (_lang1 == NULL)
	                                {
	                                   la1=(char*)realloc(la1,strlen(data->lang1name)+1);
	                                   sprintf(la1,"%s",data->lang1name);
	                                } else
	                                {
	                                   la1=(char*)realloc(la1,strlen(_lang1)+1);
	                                   sprintf(la1,"%s",_lang1);
	                                } 
	                           };
	   DeleteSpaceBegEnd (la1);
	   if (GetStringColumn(la2,S,"::",3)!=0) 
	                           {
	                              if (_lang2 == NULL)
	                                {
	                                  la2=(char*)realloc(la2,strlen(data->lang2name)+1);
	                                  sprintf(la2,"%s",data->lang2name);
	                                } else
	                                {
	                                  la2=(char*)realloc(la2,strlen(_lang2)+1);
	                                  sprintf(la2,"%s",_lang2);
	                                } 
	                           };
	   DeleteSpaceBegEnd (la2);
	   
	   if (GetStringColumn(group,S,"::",4)!=0) 
	                           {
	                             if (_group == NULL)
	                               {
	                                 group=(char*)realloc(group,1);
	                                 group[0]=0;
	                               } else
	                               {
	                                 group=(char*)realloc(group,strlen(_group)+1);
	                                 sprintf(group,"%s",_group); 
	                               }
	                           }
	   DeleteSpaceBegEnd (group);
	   if (GetStringColumn(panels,S,"::",5)!=0) 
	                           {
	                             panels=(char*)realloc(panels,strlen("0")+1);
	                             strcpy(panels,"0");
	                           };
	   if (GetStringColumn(dayss,S,"::",6)!=0) 
	                           {
	                             dayss=(char*)realloc(dayss,strlen("0")+1);
	                             strcpy(dayss,"0");
	                           };
	   centry_set(entry, la1,la2, lang1, lang2, group, atoi(panels),atoi(dayss));
	   
	   g_array_append_val(data->cwordlist,entry);
	   free(S);free(lang1);free(lang2);free(la1);free(la2);free(group);free(panels);free(dayss);
	   
        }
    fclose(f);
}


void cdata_savedicfile(cDATA *data)
{
    FILE *f;
    cENTRY *entry;
    int i;
    f = fopen(data->dictfile,"w");
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
    if (data->dictfile!=NULL)
       {
          free(data->dictfile);
          data->dictfile=NULL;
       }
    if (data->configdir!=NULL)
       {
          free(data->configdir);
          data->configdir=NULL;
       }
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

/*void cdata_saveXMLWordList(cDATA *data, char *filename)
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
}*/
