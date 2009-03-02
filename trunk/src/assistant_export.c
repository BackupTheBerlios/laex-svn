#include "assistant_export.h"
#include "main_window.h"
#include "data.h"


void assistant_export_onConnect(GtkWidget *assistant_export, gpointer user_data)
{
   cDATA* data;
   data = (cDATA*) user_data;
   g_signal_connect(assistant_export,"cancel", G_CALLBACK(assistant_export_onQuit),user_data);
   g_signal_connect(assistant_export,"close", G_CALLBACK(assistant_export_onQuit),user_data);
   g_signal_connect(gtk_builder_get_object (data->assistant_export_ui,"filechooserbuttonExportDir"),"file-set",G_CALLBACK(assistant_export_onfilechooserbuttonExportDir),user_data);
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
  GtkComboBox *comboboxGroup;
  GtkListStore *liststore;
  GtkCellLayout   *layout;
  GtkCellRenderer *cell;
  GtkTreeIter iter;
  data = (cDATA*) user_data;
  int i;
  
  comboboxGroup = GTK_COMBO_BOX(gtk_builder_get_object (data->assistant_export_ui,"comboboxgroup"));
  assistantExport = GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport"));
  
  liststore = GTK_LIST_STORE(gtk_combo_box_get_model (comboboxGroup));
    if (liststore==NULL)
      {
       liststore =  gtk_list_store_new(1,G_TYPE_STRING);
       gtk_combo_box_set_model(comboboxGroup,GTK_TREE_MODEL(liststore));
       layout = GTK_CELL_LAYOUT (comboboxGroup);
       cell = gtk_cell_renderer_text_new ();
       gtk_cell_layout_pack_start (layout, cell, TRUE);
       gtk_cell_layout_set_attributes (layout, cell,
                                  "text", 0,
                                  NULL);
       g_object_unref (liststore);
       }
   gtk_list_store_clear(liststore);
   gtk_list_store_append(liststore, &iter);
   gtk_list_store_set (liststore, &iter,0,_("All Groups"), -1);
   for (i=0;i!=(int)data->grouplist->len;i++)
      {
         gtk_list_store_append(liststore, &iter);
         gtk_list_store_set (liststore, &iter,0,g_array_index (data->grouplist, char*, i), -1);
      }

      gtk_combo_box_set_active(comboboxGroup,0);
   
  
  
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),0),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),1),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),2),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),3),TRUE);
  gtk_assistant_set_page_complete(GTK_ASSISTANT(assistantExport),gtk_assistant_get_nth_page (GTK_ASSISTANT(assistantExport),4),TRUE);
  gtk_assistant_set_current_page(GTK_ASSISTANT(assistantExport),0);
  
  gtk_widget_show (assistantExport);
}

void assistant_export_onQuit (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  g_print("... assistant_export_onQuit\n");
  data = (cDATA*) user_data;
  gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object (data->assistant_export_ui,"assistantExport")));
}

void assistant_export_onfilechooserbuttonExportDir (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  GtkWidget *assistantExport;
  g_print("... assistant_export_onfilechooserbuttonExportDir");  
}

void assistant_export_onapllypressed (GtkWidget *widget, gpointer user_data)
{
  cDATA* data;
  g_print("... assistant_export_onapllypressed\n");
  data = (cDATA*) user_data;
}

void assistant_export_delete(gpointer user_data)
{
  cDATA* data;
  data = (cDATA*) user_data;
  g_object_unref(G_OBJECT(data->assistant_export_ui));
}

