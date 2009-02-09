#include "assistant_export.h"
#include "main_window.h"
#include "data.h"

char *exportfile;

void assistant_export_onConnect(GtkWidget *assistant_export, gpointer user_data)
{
   cDATA* data;
   data = (cDATA*) user_data;
   g_signal_connect(assistant_export,"cancel", G_CALLBACK(assistant_export_onQuit),user_data);
   g_signal_connect(assistant_export,"close", G_CALLBACK(assistant_export_onQuit),user_data);
   g_signal_connect(gtk_builder_get_object (data->assistant_export_ui,"filechooserbuttonExportFile"),"file-set",G_CALLBACK(assistant_export_onfilechooserbuttonExportFile),user_data);
   g_signal_connect(gtk_builder_get_object (data->assistant_export_ui,"assistantExport"),"apply",G_CALLBACK(assistant_export_onapllypressed),user_data);
}

void assistant_export_init(gpointer user_data)
{
   cDATA* data;
   GtkWidget *assistantExport;
   GtkComboBox *comboboxFileformat;
   GtkListStore *liststore;
   GtkCellLayout   *layout;
   GtkCellRenderer *cell;
   GtkTreeIter iter;
   data = (cDATA*) user_data;
   exportfile=NULL;
   data->assistant_export_ui = gtk_builder_new ();
   gtk_builder_add_from_file(data->assistant_export_ui,UI_PATH"assistant_export.ui",NULL);
   assistantExport = GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),0),_("Introduction"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),1),_("Choose a file"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),2),_("Options"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),3),_("Confirmation"));
   gtk_assistant_set_page_title(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),4),_("Summery"));
   /* init comboxFileformat: */
   comboboxFileformat = GTK_COMBO_BOX(gtk_builder_get_object (data->assistant_export_ui,"comboboxFileformat"));
   liststore =  gtk_list_store_new(1,G_TYPE_STRING);
   gtk_combo_box_set_model(comboboxFileformat,GTK_TREE_MODEL(liststore));
   layout = GTK_CELL_LAYOUT (comboboxFileformat);
   cell = gtk_cell_renderer_text_new ();
   gtk_cell_layout_pack_start (layout, cell, TRUE);
   gtk_cell_layout_set_attributes (layout, cell,
                                   "text", 0,
                                    NULL);
   gtk_list_store_append(liststore, &iter);
   gtk_list_store_set (liststore, &iter,0,_("LaEx Dictionary format"), -1);
   gtk_list_store_append(liststore, &iter);
   gtk_list_store_set (liststore, &iter,0,_("Das DING dictionary format"), -1);
   gtk_list_store_append(liststore, &iter);
   gtk_list_store_set (liststore, &iter,0,_("Text CSV format"), -1);
   g_object_unref (liststore);
   gtk_combo_box_set_active(comboboxFileformat,0);
    
   /* signal connect: */
   assistant_export_onConnect(assistantExport,user_data);
}

void assistant_export_run(gpointer user_data)
{
  cDATA* data;
  GtkWidget *assistantExport;
  data = (cDATA*) user_data;
  assistantExport = GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport"));
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),0),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),1),FALSE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),2),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),3),TRUE);
   gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),4),TRUE);
  gtk_assistant_set_current_page(GTK_ASSISTANT(assistantExport),0);
  //assistant_export_onfilechooserbuttonExportFile(NULL,user_data);
  gtk_widget_show (assistantExport);
}

void assistant_export_onQuit (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  g_print("... assistant_export_onQuit\n");
  data = (cDATA*) user_data;
  gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport")));
  if (exportfile!=NULL)
    {
      g_free(exportfile);
      exportfile=NULL;
    }
}

void assistant_export_onfilechooserbuttonExportFile (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  GtkWidget *assistantExport;
  g_print("... assistant_export_onfilechooserbuttonExportFile");
  data = (cDATA*) user_data;
  assistantExport = GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport"));
  if (exportfile!=NULL)
    {
      g_free(exportfile);
      exportfile=NULL;
    }
  exportfile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_builder_get_object (data->assistant_export_ui,"filechooserbuttonExportFile")));
  if (exportfile == NULL)
      {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),1),FALSE);
        return;
      }
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),1),TRUE);   
}

void assistant_export_onapllypressed (GtkWidget *widget, gpointer user_data)
{
 /* cDATA* data;
  g_print("... assistant_import_onapllypressed\n");
  data = (cDATA*) user_data;
  cdata_loaddicfile(data,importfile,(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang1"))),(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrylang2"))),(char*)gtk_entry_get_text (GTK_ENTRY(gtk_builder_get_object (data->assistant_import_ui,"entrygroup"))),FALSE);
  main_window_Show_treeviewGroup(user_data);*/
  //g_signal_emit_by_name(G_OBJECT(gtk_builder_get_object (data->assistant_import_ui,"assistantImport")), "cancel");
}

void assistant_export_delete(gpointer user_data)
{
  cDATA* data;
  data = (cDATA*) user_data;
  if (exportfile!=NULL)
    {
      g_free(exportfile);
      exportfile=NULL;
    }
  g_object_unref(G_OBJECT(data->assistant_export_ui));
}

