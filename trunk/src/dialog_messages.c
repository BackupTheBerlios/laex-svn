#include <string.h>
#include "dialog_messages.h"
#include "data.h"

void dialog_message (gchar *message) 
{
  GtkWidget *dialog, *label, *content_area,*alig;
  dialog = gtk_dialog_new_with_buttons (_("Message!"),
                                         NULL,
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
            content_area = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);//gtk_dialog_get_content_area (GTK_DIALOG (dialog2));
            label = gtk_label_new (message);
            alig = gtk_alignment_new(0.5,0.5,0.5,0.5);
            gtk_alignment_set_padding ( GTK_ALIGNMENT(alig),48,48,24,24);
            gtk_container_add (GTK_CONTAINER (content_area), alig);
            gtk_container_add (GTK_CONTAINER (alig), label);
            gtk_widget_show_all (dialog);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
}

gint dialog_question(gchar *message)
{
   GtkWidget *dialog, *label, *content_area,*alig;
   gint result;
   dialog = gtk_dialog_new_with_buttons (_("Question!"),
                                         NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_YES,
                                         GTK_RESPONSE_YES,
                                         GTK_STOCK_NO,
                                         GTK_RESPONSE_NO,
                                         NULL);
   content_area = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);//gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new (message);
   alig = gtk_alignment_new(0.5,0.5,0.5,0.5);
   gtk_alignment_set_padding ( GTK_ALIGNMENT(alig),48,48,24,24);
   gtk_container_add (GTK_CONTAINER (content_area), alig);
   gtk_container_add (GTK_CONTAINER (alig), label);
   gtk_widget_show_all (dialog);
   result = gtk_dialog_run (GTK_DIALOG (dialog));
   gtk_widget_destroy (dialog);
   return result;
}

gchar *dialog_input(gchar* title,gchar *message, gchar *templ)
{
   GtkWidget *dialog, *label, *content_area,*alig,*cont2,*entry;
   gint result;
   gchar *resultS;
   gchar *S;
   resultS=NULL;
   S=NULL;
   dialog = gtk_dialog_new_with_buttons (title,
                                         NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_OK,
                                         NULL);
   content_area = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);//gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   alig = gtk_alignment_new(0.5,0.5,0.5,0.5);
   gtk_alignment_set_padding ( GTK_ALIGNMENT(alig),24,24,24,24);
   cont2 = gtk_vbox_new(FALSE,5);
   label = gtk_label_new (message);
   entry = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(entry),templ);
   gtk_container_add (GTK_CONTAINER (content_area), alig);
   gtk_container_add (GTK_CONTAINER (alig), cont2);
   gtk_container_add (GTK_CONTAINER (cont2), label);
   gtk_container_add (GTK_CONTAINER (cont2), entry);
   gtk_widget_show_all (dialog);
   result = gtk_dialog_run (GTK_DIALOG (dialog));
   if (result==GTK_RESPONSE_OK)
      {
         S=(gchar*)gtk_entry_get_text(GTK_ENTRY(entry));
         resultS=(gchar*)malloc(strlen(S)+1);
         strcpy(resultS,S);
      }
   gtk_widget_destroy (dialog);
   return resultS;
}
