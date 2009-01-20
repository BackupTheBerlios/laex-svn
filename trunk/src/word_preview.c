/***************************************************************************
 *            word_preview.c
 *
 *  Tue Jan 13 14:57:24 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#include "word_preview.h"
#include "data.h"
#include "centry.h"
#include "main_window.h"
#include "statistics.h"
#include "dialog_messages.h"

void main_window_ontoolbuttonWordPreview(GtkWidget *widget, gpointer user_data)
{
    int i;
    cENTRY *entry;
    cDATA *data;
    static char S[100];
    GtkDialog *dialog;
    gint result;
    gboolean allWords;
    GtkComboBox *comboboxSelectWords;
    
	
    g_print("... main_window_ontoolbuttonWordPreview\n");
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
            dialog_message(_("There are no Words selected in this group!\nOnly words from Panel 1 to 4 will be asked!"));
            return;
        }
    // randomize:
    //
	
    
    if (data->traindirection==TRUE)
		{
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPreviewLAsked")),data->lang1name);
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPreviewLAnswered")),data->lang2name);
		} else
		{
	      gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPreviewLAsked")),data->lang2name);
		  gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelWordPreviewLAnswered")),data->lang1name);
		}
    data->trainindex=-1;
    data->trainasked=TRUE;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPreview")),0.0);
    sprintf(S,"%d%%    ( %d / %d )",0,0,(int)data->trainlist->len);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPreview")),S);
    main_window_onbtnWordPreviewNext(widget,user_data);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),3);
}

void main_window_onbtnWordPreviewNext(GtkWidget *widget, gpointer user_data)
{
    cENTRY *entry;
    cDATA *data;
    static char S[100];
    g_print("... main_window_onbtnWordPreviewNext\n");
    data=(cDATA*)user_data;
    if (data->trainasked==TRUE) data->trainindex++;
    if ((data->trainindex >= (int)data->trainlist->len))
      {
          main_window_ontoolbuttonWordPreviewBack(widget,user_data);
          return;
      }
    entry = g_array_index (data->trainlist, cENTRY*, data->trainindex);
    if (data->trainasked==TRUE)
      {
		if (data->traindirection==TRUE)
		  {
            gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"entryWordPreviewLAsked")),entry->word1);
		  } else
		  {
			gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"entryWordPreviewLAsked")),entry->word2);  
		  }
        gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"entryWordPreviewLAnswered")),"");  
      } else
      {
        if (data->traindirection==TRUE)
		  {
		    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"entryWordPreviewLAnswered")),entry->word2);    
		  } else
		  {
			gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object (data->main_window_ui,"entryWordPreviewLAnswered")),entry->word1);    
		  }
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPreview")),((double)data->trainindex+1)/((double)data->trainlist->len));
        sprintf(S,"%d%%    ( %d / %d )",(int)(((double)data->trainindex+1)*100.5/((double)data->trainlist->len)),(int)(data->trainindex+1),(int)data->trainlist->len);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gtk_builder_get_object (data->main_window_ui,"progressbarWordPreview")),S);
      }
    data->trainasked ^= 1;
}

void main_window_ontoolbuttonWordPreviewBack(GtkWidget *widget, gpointer user_data)
{
    cDATA *data;
    g_print("... main_window_ontoolbuttonWordPreviewBack\n");
    data=(cDATA*)user_data;
    g_array_free(data->trainlist,TRUE);
    main_window_ontoolbuttonStatistics(widget,user_data);
}
