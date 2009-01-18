/***************************************************************************
 *            select_words.c
 *
 *  Tue Jan 13 14:57:24 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#include "select_words.h"
#include "data.h"
#include "centry.h"
#include "main_window.h"

void main_window_init_comboboxSelectWords(gpointer user_data)
{
 cDATA* data;
 GtkComboBox *comboboxSelectWords;
 GtkListStore *liststore;
 GtkCellLayout   *layout;
 GtkCellRenderer *cell;
 GtkTreeIter iter;
 data = (cDATA*) user_data;
 comboboxSelectWords = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectWords"));
 liststore =  gtk_list_store_new(1,G_TYPE_STRING);
 gtk_combo_box_set_model(comboboxSelectWords,GTK_TREE_MODEL(liststore));
 layout = GTK_CELL_LAYOUT (comboboxSelectWords);
 cell = gtk_cell_renderer_text_new ();
 gtk_cell_layout_pack_start (layout, cell, TRUE);
 gtk_cell_layout_set_attributes (layout, cell,
                                  "text", 0,
                                  NULL);
 gtk_list_store_append(liststore, &iter);
 gtk_list_store_set (liststore, &iter,0,"Panel 0", -1);
 gtk_list_store_append(liststore, &iter);
 gtk_list_store_set (liststore, &iter,0,"Panel 1", -1);
 gtk_list_store_append(liststore, &iter);
 gtk_list_store_set (liststore, &iter,0,"Panel 2", -1);
 gtk_list_store_append(liststore, &iter);
 gtk_list_store_set (liststore, &iter,0,"Panel 3", -1);
 gtk_list_store_append(liststore, &iter);
 gtk_list_store_set (liststore, &iter,0,"Panel 4", -1);
 g_object_unref (liststore);
}

void main_window_ontoolbuttonSelectWordsInit(GtkWidget *widget, gpointer user_data)
{
    cDATA* data;
    GtkComboBox *comboboxSelectGroup,*comboboxSelectWords;
    GtkListStore *liststore;
    GtkCellLayout   *layout;
    GtkCellRenderer *cell;
    GtkTreeIter iter;
    int i;

    g_print("... main_window_ontoolbuttonSelectWordsInit\n");
    data = (cDATA*) user_data;
    comboboxSelectGroup = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup"));
    comboboxSelectWords = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectWords"));
    liststore = GTK_LIST_STORE(gtk_combo_box_get_model (comboboxSelectGroup));
    if (liststore==NULL)
      {
       liststore =  gtk_list_store_new(1,G_TYPE_STRING);
       gtk_combo_box_set_model(comboboxSelectGroup,GTK_TREE_MODEL(liststore));
       layout = GTK_CELL_LAYOUT (comboboxSelectGroup);
       cell = gtk_cell_renderer_text_new ();
       gtk_cell_layout_pack_start (layout, cell, TRUE);
       gtk_cell_layout_set_attributes (layout, cell,
                                  "text", 0,
                                  NULL);
       g_object_unref (liststore);
       }
      gtk_list_store_clear(liststore);
      for (i=0;i!=(int)data->grouplist->len;i++)
      {
         gtk_list_store_append(liststore, &iter);
         gtk_list_store_set (liststore, &iter,0,g_array_index (data->grouplist, char*, i), -1);
      }

      gtk_combo_box_set_active(comboboxSelectGroup,0);
      gtk_combo_box_set_active(comboboxSelectWords,0);
      main_window_ontoolbuttonSelectWords(widget,user_data);
}

void main_window_ontoolbuttonSelectWords(GtkWidget *widget, gpointer user_data)
{
        cDATA* data;
        g_print("... main_window_ontoolbuttonSelectWords\n");
        data = (cDATA*) user_data;
        gtk_notebook_set_current_page(GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),2); 
}

void main_window_init_treeviewSelectWords(gpointer user_data)
{
     cDATA *data;
     GtkTreeViewColumn   *col;
     GtkCellRenderer     *renderer;

     data = (cDATA*) user_data;


     col = gtk_tree_view_column_new();
     gtk_tree_view_column_set_title(col, "German");
     gtk_tree_view_append_column(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords")), col);
     renderer = gtk_cell_renderer_text_new();
     gtk_tree_view_column_pack_start(col, renderer, TRUE);
     gtk_tree_view_column_set_sizing(col,GTK_TREE_VIEW_COLUMN_FIXED);
     gtk_tree_view_column_set_fixed_width(col,200);
     gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN (col), TRUE);
     gtk_tree_view_column_add_attribute(col, renderer, "text", 0);
     col = gtk_tree_view_column_new();
     gtk_tree_view_column_set_title(col, "English");
     gtk_tree_view_column_set_fixed_width(col,200);
     gtk_tree_view_append_column(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords")), col);
     renderer = gtk_cell_renderer_text_new();
     gtk_tree_view_column_pack_start(col, renderer, TRUE);
     gtk_tree_view_column_add_attribute(col, renderer, "text", 1);
}

void main_window_change_treeviewSelectWords(gpointer user_data)
{
     GtkComboBox *comboboxSelectWords, *comboboxSelectGroup;
     GtkTreeView *view;
     GtkTreeModel *model;
     GtkTreeIter iter;
     cDATA *data;
     cENTRY *entry;
     char *group;
     int i;

     data = (cDATA*) user_data; 
	 comboboxSelectWords = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectWords"));
     comboboxSelectGroup = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup"));
     

     // if Panel 0 button Panel to Panel is not sensitive:
     if (gtk_combo_box_get_active (comboboxSelectWords)==0)
         {
           gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"buttonToPanel0")),FALSE);
         } else
         {
           gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"buttonToPanel0")),TRUE);
         }
      if (gtk_combo_box_get_active (comboboxSelectWords)==1)
         {
           gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"buttonToPanel1")),FALSE);
         } else
         {
           gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"buttonToPanel1")),TRUE);
         }
         
    view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords"));
    model = gtk_tree_view_get_model (view);
    if (model==NULL)
      {
	       model= GTK_TREE_MODEL(gtk_tree_store_new(3,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_POINTER));
             gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
             g_object_unref(model); /* destroy model automatically with view */
             gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),GTK_SELECTION_MULTIPLE);
      }
    gtk_tree_store_clear (GTK_TREE_STORE(model));
    group = gtk_combo_box_get_active_text (comboboxSelectGroup);
    if (group==NULL) return;
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
        entry = g_array_index (data->cwordlist, cENTRY*, i); 
        if ((centry_groupexist(entry,group)==TRUE) && (gtk_combo_box_get_active(comboboxSelectWords)==(int)entry->panel))
          {
                 gtk_tree_store_append(GTK_TREE_STORE(model), &iter, NULL);
                                gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
                                0, entry->word1,
                                1, entry->word2,
                                2,entry,
                                -1);
          }
      }
    
}

void main_window_copy_selected_to_Panel1(GtkTreeModel *model,GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
    cENTRY *entry;
    gtk_tree_model_get (model, iter, 2, &entry, -1);
    entry->panel=1;
}

void main_window_copy_selected_to_Panel0(GtkTreeModel *model,GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
    cENTRY *entry;
    gtk_tree_model_get (model, iter, 2, &entry, -1);
    entry->panel=0;
}

void main_window_onbuttonToPanel1(GtkWidget *widget, gpointer user_data)
{
    GtkTreeView *view;
    GtkTreeSelection *selection;
	cDATA *data;
    
    g_print("... main_window_onbuttonToPanel1\n");
	
    data = (cDATA*) user_data; 
    view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords"));
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_tree_selection_selected_foreach (selection,main_window_copy_selected_to_Panel1,user_data);
    main_window_change_treeviewSelectWords(user_data);
}

void main_window_onbuttonToPanel0(GtkWidget *widget,gpointer user_data)
{
    GtkTreeView *view;
    GtkTreeSelection *selection;
    cDATA *data;
    g_print("... main_window_onbuttonToPanel0\n");
    data = (cDATA*) user_data; 
    view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords"));
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_tree_selection_selected_foreach (selection,main_window_copy_selected_to_Panel0,user_data);
    main_window_change_treeviewSelectWords(user_data);
}


void main_window_oncomboboxSelectGroup(GtkComboBox *widget, gpointer user_data)
{
    g_print("... main_window_oncomboboxSelectGroup\n");
    main_window_change_treeviewSelectWords(user_data);
}

void main_window_oncomboboxSelectWords(GtkComboBox *widget, gpointer user_data)
{
    g_print("... main_window_oncomboboxSelectWords\n");
    main_window_change_treeviewSelectWords(user_data);
}

void main_window_onbtnSelectWordsSelectAll(GtkWidget *widget, gpointer user_data)
{
    GtkTreeView *view;
    GtkTreeSelection *selection;
    cDATA *data;
    g_print("... main_window_onbtnSelectWordsSelectAll\n");
    data = (cDATA*) user_data;
    view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewSelectWords"));
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_tree_selection_select_all (selection);
}

void main_window_onbtnSelectWordsToPanel1(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog, *label, *content_area,*alig;
    cDATA *data;
    data = (cDATA*) user_data;
    int i;
    cENTRY *entry;
    GtkComboBox *comboboxSelectGroup;
    char *group;
    g_print("... main_window_onbtnSelectWordsToPanel1\n");
    comboboxSelectGroup = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup"));
    group = gtk_combo_box_get_active_text (comboboxSelectGroup);
    dialog = gtk_dialog_new_with_buttons (_("Question!"),
                                         GTK_WINDOW(gtk_builder_get_object (data->main_window_ui,"main_window")),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_YES,
                                         GTK_RESPONSE_YES,
                                         GTK_STOCK_NO,
                                         GTK_RESPONSE_NO,
                                         NULL);
   content_area = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);//gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new (_("Are you sure that you want to put every word in this group (2-4) to Panel 1?"));
   //gtk_unref(label);
   alig = gtk_alignment_new(0.5,0.5,0.5,0.5);
   gtk_alignment_set_padding ( GTK_ALIGNMENT(alig),48,48,24,24);
   gtk_container_add (GTK_CONTAINER (content_area), alig);
   gtk_container_add (GTK_CONTAINER (alig), label);
   gtk_widget_show_all (dialog);
   gint result = gtk_dialog_run (GTK_DIALOG (dialog));
   if (result==GTK_RESPONSE_YES)
     {
        for (i=0;i!=(int)data->cwordlist->len;i++)
           {
              entry = g_array_index (data->cwordlist, cENTRY*, i);
              if ((entry->panel>0) && (centry_groupexist(entry,group)==TRUE))
                {
                   entry->panel=1;
                }
           } 
       
     }
  gtk_widget_destroy (dialog);
  main_window_change_treeviewSelectWords(user_data);
}

void main_window_onbtnSelectWordsToPanel0(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog, *label, *content_area,*alig;
    cDATA *data;
    data = (cDATA*) user_data;
    int i;
    cENTRY *entry;
    GtkComboBox *comboboxSelectGroup;
    char *group;
    g_print("... main_window_onbtnSelectWordsToPanel0\n");
    comboboxSelectGroup = GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup"));
    group = gtk_combo_box_get_active_text (comboboxSelectGroup);
    dialog = gtk_dialog_new_with_buttons (_("Question!"),
                                         GTK_WINDOW(gtk_builder_get_object (data->main_window_ui,"main_window")),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_YES,
                                         GTK_RESPONSE_YES,
                                         GTK_STOCK_NO,
                                         GTK_RESPONSE_NO,
                                         NULL);
   content_area = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);//gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new (_("Are you sure that you want to put every word to Panel 0?"));
   //gtk_unref(label);
   alig = gtk_alignment_new(0.5,0.5,0.5,0.5);
   gtk_alignment_set_padding ( GTK_ALIGNMENT(alig),48,48,24,24);
   gtk_container_add (GTK_CONTAINER (content_area), alig);
   gtk_container_add (GTK_CONTAINER (alig), label);
   gtk_widget_show_all (dialog);
   gint result = gtk_dialog_run (GTK_DIALOG (dialog));
   if (result==GTK_RESPONSE_YES)
     {
        for (i=0;i!=(int)data->cwordlist->len;i++)
           {
              entry = g_array_index (data->cwordlist, cENTRY*, i);
              if (centry_groupexist(entry,group)==TRUE)
                {
                   entry->panel=0;
                }
           } 
       
     }
  gtk_widget_destroy (dialog);
  main_window_change_treeviewSelectWords(user_data);
}

