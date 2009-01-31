#include "assistant_import.h"
#include "main_window.h"
#include "data.h"

char *importfile;

void assistant_import_onConnect(GtkWidget *assistant_import, gpointer user_data)
{
   cDATA* data;
   data = (cDATA*) user_data;
   g_signal_connect(assistant_import,"cancel", G_CALLBACK(assistant_import_onQuit),user_data);
   g_signal_connect(assistant_import,"close", G_CALLBACK(assistant_import_onQuit),user_data);
   g_signal_connect(gtk_builder_get_object (data->assistant_import_ui,"filechooserbuttonImportFile"),"file-set",G_CALLBACK(assistant_import_onfilechooserbuttonImportFile),user_data);
   g_signal_connect(gtk_builder_get_object (data->assistant_import_ui,"assistantImport"),"apply",G_CALLBACK(assistant_import_onapllypressed),user_data);
}

void assistant_import_init(gpointer user_data)
{
   cDATA* data;
   GtkWidget *assistantImport;
   GtkComboBox *comboboxFileformat;
   GtkListStore *liststore;
   GtkCellLayout   *layout;
   GtkCellRenderer *cell;
   GtkTreeIter iter;
   data = (cDATA*) user_data;
   importfile=NULL;
   data->assistant_import_ui = gtk_builder_new ();
   gtk_builder_add_from_file(data->assistant_import_ui,UI_PATH"assistant_import.ui",NULL);
   assistantImport = GTK_WIDGET(gtk_builder_get_object (data->assistant_import_ui,"assistantImport"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),0),_("Introduction"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),1),_("Choose a file"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),2),_("Options"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),3),_("Confirmation"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),4),_("Summery"));
   /* init comboxFileformat: */
   comboboxFileformat = GTK_COMBO_BOX(gtk_builder_get_object (data->assistant_import_ui,"comboboxFileformat"));
   liststore =  gtk_list_store_new(1,G_TYPE_STRING);
   gtk_combo_box_set_model(comboboxFileformat,GTK_TREE_MODEL(liststore));
   layout = GTK_CELL_LAYOUT (comboboxFileformat);
   cell = gtk_cell_renderer_text_new ();
   gtk_cell_layout_pack_start (layout, cell, TRUE);
   gtk_cell_layout_set_attributes (layout, cell,
                                   "text", 0,
                                    NULL);
   gtk_list_store_append(liststore, &iter);
   gtk_list_store_set (liststore, &iter,0,_("Das DING dictionary format"), -1);
   g_object_unref (liststore);
   gtk_combo_box_set_active(comboboxFileformat,0);
   
   gtk_entry_set_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang1")),_("German"));
   gtk_entry_set_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang2")),_("English"));
     
   /* signal connect: */
   assistant_import_onConnect(assistantImport,user_data);
}

void assistant_import_run(gpointer user_data)
{
  cDATA* data;
  GtkWidget *assistantImport;
  data = (cDATA*) user_data;
  assistantImport = GTK_WIDGET(gtk_builder_get_object (data->assistant_import_ui,"assistantImport"));
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),0),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),1),FALSE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),2),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),3),TRUE);
   gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),4),TRUE);
  gtk_assistant_set_current_page(GTK_ASSISTANT(assistantImport),0);
  assistant_import_onfilechooserbuttonImportFile(NULL,user_data);
  gtk_widget_show (assistantImport);
}

void assistant_import_onQuit (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  g_print("... assistant_import_onQuit\n");
  data = (cDATA*) user_data;
  gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object (data->assistant_import_ui,"assistantImport")));
  if (importfile!=NULL)
    {
      g_free(importfile);
      importfile=NULL;
    }
}

void assistant_import_onfilechooserbuttonImportFile (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  GtkWidget *assistantImport;
  g_print("... assistant_import_onfilechooserbuttonImportFile\n");
  data = (cDATA*) user_data;
  assistantImport = GTK_WIDGET(gtk_builder_get_object (data->assistant_import_ui,"assistantImport"));
  if (importfile!=NULL)
    {
      g_free(importfile);
      importfile=NULL;
    }
  importfile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_builder_get_object (data->assistant_import_ui,"filechooserbuttonImportFile")));
  if (importfile == NULL)
      {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),1),FALSE);
        return;
      }
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantImport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantImport),1),TRUE);   
}

void assistant_import_onapllypressed (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  g_print("... assistant_import_onapllypressed\n");
  data = (cDATA*) user_data;
  cdata_loaddicfile(data,importfile,(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang1"))),(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang2"))),(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrygroup"))),FALSE);
  main_window_Show_treeviewGroup(user_data);
  //g_signal_emit_by_name(G_OBJECT(gtk_builder_get_object (data->assistant_import_ui,"assistantImport")), "cancel");
}

void assistant_import_delete(gpointer user_data)
{
  cDATA* data;
  data = (cDATA*) user_data;
  if (importfile!=NULL)
    {
      g_free(importfile);
      importfile=NULL;
    }
  g_object_unref(G_OBJECT(data->assistant_import_ui));
}

