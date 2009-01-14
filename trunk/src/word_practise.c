/***************************************************************************
 *            word_practise.c
 *
 *  Tue Jan 13 15:59:51 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#include <string.h>
#include "word_practise.h"
#include "data.h"
#include "centry.h"
#include "main_window.h"
#include "statistics.h"

void main_window_ontoolbuttonWordPractise(GtkWidget *widget, gpointer user_data)
{
    
    int i;
    cENTRY *entry;
    cDATA *data;
    static char S[100];
	GtkDialog *dialog;
	gint result;
	gboolean allWords;
	GtkComboBox *comboboxSelectWords;
	
    g_print("... main_window_ontoolbuttonWordPractise\n");
    data=(cDATA*)user_data;
	
	dialog = GTK_DIALOG (gtk_builder_get_object (data->dialog_start_training_ui,"dialogStartTraining"));
	comboboxSelectWords = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectWords"));
	result = gtk_dialog_run (dialog);
    gtk_widget_hide(GTK_WIDGET(dialog));
	if (result==GTK_RESPONSE_OK)
      {
        if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (data->dialog_start_training_ui,"radiobuttonlang1lang2")))==TRUE)   
		   {
			   data->traindirection=TRUE;
		   } else
		   {
			   data->traindirection=FALSE;
		   }
	    allWords=gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (data->dialog_start_training_ui,"radiobuttonaskedwordsall")));
      } else
	  {
          return;
	  }
	
    data->trainlist=g_array_new(TRUE,FALSE,sizeof(cENTRY*));
    data->traingroup=gtk_combo_box_get_active_text(GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup")));
	
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
        entry = g_array_index (data->cwordlist, cENTRY*, i);
        if ((entry->panel>0)&&(entry->days==0)&&(centry_groupexist(entry,data->traingroup)==TRUE))
          {
             if (allWords==TRUE)
			  {
				  g_array_append_val(data->trainlist,entry);
			  } else
			  {
				  if (entry->panel==gtk_combo_box_get_active (comboboxSelectWords))
				     {
						 g_array_append_val(data->trainlist,entry);
					 }
			  }
          }
       }
    if (data->trainlist->len==0)
        {
            g_array_free(data->trainlist,TRUE);
            return;
        }
    // randomize:
    //
	
    
    if (data->traindirection==TRUE)
		{
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAsked")),data->lang1name);
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")),data->lang2name);
		} else
		{
	      gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAsked")),data->lang2name);
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")),data->lang1name);
		}
    data->trainindex=-1;
    data->trainasked=TRUE;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPractise")),0.0);
    sprintf(S,"%d%%    ( %d / %d )",0,0,(int)data->trainlist->len);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPractise")),S);
    main_window_WordPractiseShowNextWord(user_data);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),4);
}

void main_window_onbtnWordPractiseOK(GtkWidget *widget, gpointer user_data)
{
}

void main_window_onbtnWordPractiseNext(GtkWidget *widget, gpointer user_data)
{
}

void main_window_ontoolbuttonWordPractiseBack(GtkWidget *widget, gpointer user_data)
{
	cDATA *data;
    g_print("... main_window_ontoolbuttonWordPractiseBack\n");
    data=(cDATA*)user_data;
    g_array_free(data->trainlist,TRUE);
    main_window_ontoolbuttonStatistics(widget,user_data);
}

void main_window_WordPractiseShowNextWord(cDATA* data)
{
	cENTRY *entry;
    static char S[100];
	const gchar *Word;
    if (data->trainasked==TRUE) 
		{
		  gtk_widget_set_sensitive(GTK_WIDGET (gtk_builder_get_object (data->main_window_ui,"btnWordPractiseOK")),TRUE);
		  data->trainindex++;
		} else
		{
		  gtk_widget_set_sensitive(GTK_WIDGET (gtk_builder_get_object (data->main_window_ui,"btnWordPractiseOK")),FALSE);
		}
    if ((data->trainindex >= (int)data->trainlist->len))
      {
          main_window_ontoolbuttonWordPractiseBack(NULL,data);
          return;
      }
    entry = g_array_index (data->trainlist, cENTRY*, data->trainindex);
    if (data->trainasked==TRUE)
      {
		if (data->traindirection==TRUE)
		  {
            gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAsked")),entry->word1);
		  } else
		  {
			gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAsked")),entry->word2);  
		  }
        gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")),"");  
      } else
      {
        if (data->traindirection==TRUE)
		  {
		    //gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")),entry->word2);    
			Word=gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")));  
			if (known((char*)Word,entry->word2)==TRUE)
				g_print("right"); else g_print("wrong");
		  } else
		  {
			//gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")),entry->word1);    
			  Word=gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"labelWordPractiseLAnswered")));  
			if (known((char*)Word,entry->word1)==TRUE)
				g_print("right"); else g_print("wrong");
		  }
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPractise")),((double)data->trainindex+1)/((double)data->trainlist->len));
        sprintf(S,"%d%%    ( %d / %d )",(int)(((double)data->trainindex+1)*100.5/((double)data->trainlist->len)),(int)(data->trainindex+1),(int)data->trainlist->len);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPractise")),S);
      }
    data->trainasked ^= 1;
}

gboolean known(char *original, char* answered)
{
	char *S,*S2,*ans2;
    int i,i2,i3;
    gboolean result;
    S = (char *)malloc(strlen(original));
    S2 = (char *)malloc(strlen(original));
	ans2 = (char *)malloc(strlen(answered));					
    i=0;
    result = FALSE;
    while (1)
     {
         if (GetStringColumn(S,original,"|",i)==1) break;
         
		 i3=0;
		 for (i2=0;i2!=strlen(S);i2++)
			{
			  if (S[i2] != ' ') 
				{S2[i3]=S[i2];
				 i3++;
				}
			}
		 i3=0;
		 for (i2=0;i2!=strlen(answered);i2++)
			{
			  if (answered[i2] != ' ') 
				{ans2[i3]=answered[i2];	
				i3++;
				}
			}
		 if (strcmp(S2,ans2)==0)
            {
               result = TRUE;
               break;
            }
         i++;
     }
    free(S);
    return result;
}


