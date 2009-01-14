/***************************************************************************
 *            dialog_edit_entry.c
 *
 *  Tue Jan 13 15:42:06 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#include "select_words.h"
#include "data.h"
#include "centry.h"
#include "dialog_edit_entry.h"

void main_window_init_comboboxPanel(gpointer user_data)
{
 cDATA* data;
 GtkComboBox *comboboxPanel;
 GtkListStore *liststore;
 GtkCellLayout   *layout;
 GtkCellRenderer *cell;
 GtkTreeIter iter;
 data = (cDATA*) user_data;
 comboboxPanel = GTK_COMBO_BOX(gtk_builder_get_object (data->dialog_edit_entry_ui,"comboboxPanel"));
 liststore =  gtk_list_store_new(1,G_TYPE_STRING);
 gtk_combo_box_set_model(comboboxPanel,GTK_TREE_MODEL(liststore));
 layout = GTK_CELL_LAYOUT (comboboxPanel);
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
 gtk_combo_box_set_active(comboboxPanel,0);
}

void main_window_onbtnNewEntry(GtkWidget *widget, gpointer user_data)
{
    cDATA* data;
    GtkWidget *dialog;
    GtkEntry *entryTranslationlang1;
    GtkEntry *entryTranslationlang2;
    GtkEntry *entryLanguageName1;
    GtkEntry *entryLanguageName2;
    GtkEntry *entryGroup;
    GtkComboBox *comboboxPanel;
    GtkSpinButton *spinbuttonDays;
    g_print("... main_window_onbtnNewEntry\n");
    data = (cDATA*) user_data;
    dialog = GTK_WIDGET(gtk_builder_get_object (data->dialog_edit_entry_ui,"dialogEditEntry"));
    entryTranslationlang1 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryTranslationlang1"));
    entryTranslationlang2 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryTranslationlang2"));
    entryLanguageName1 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryLanguageName1"));
    entryLanguageName2 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryLanguageName2"));
    entryGroup = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryGroup"));
    comboboxPanel = GTK_COMBO_BOX(gtk_builder_get_object (data->dialog_edit_entry_ui,"comboboxPanel"));
    spinbuttonDays = GTK_SPIN_BUTTON(gtk_builder_get_object (data->dialog_edit_entry_ui,"spinbuttonDays"));
    data = (cDATA*) user_data;
    
    gtk_entry_set_text(entryTranslationlang1,"");
    gtk_entry_set_text(entryTranslationlang2,"");
    gtk_entry_set_text(entryLanguageName1,"Deutsch");
    gtk_entry_set_text(entryLanguageName2,"Englisch");
    gtk_entry_set_text(entryGroup,"");
    gtk_spin_button_set_value(spinbuttonDays,(gdouble)0);
    if (gtk_dialog_run (GTK_DIALOG(dialog))==GTK_RESPONSE_OK)
      {
            
      }
    gtk_widget_hide(dialog);
}

void main_window_onbtnEditEntry(GtkWidget *widget, gpointer user_data)
{
    cDATA* data;
    GtkWidget *dialog;
    GtkEntry *entryTranslationlang1;
    GtkEntry *entryTranslationlang2;
    GtkEntry *entryLanguageName1;
    GtkEntry *entryLanguageName2;
    GtkEntry *entryGroup;
    GtkComboBox *comboboxPanel;
    GtkSpinButton *spinbuttonDays;
    GtkTreeSelection* sel;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeStore *treestore;
    cENTRY *entry;
    
    g_print("... main_window_onbtnEditEntry\n");
    data = (cDATA*) user_data;
    dialog = GTK_WIDGET(gtk_builder_get_object (data->dialog_edit_entry_ui,"dialogEditEntry"));
    entryTranslationlang1 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryTranslationlang1"));
    entryTranslationlang2 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryTranslationlang2"));
    entryLanguageName1 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryLanguageName1"));
    entryLanguageName2 = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryLanguageName2"));
    entryGroup = GTK_ENTRY(gtk_builder_get_object (data->dialog_edit_entry_ui,"entryGroup"));
    comboboxPanel = GTK_COMBO_BOX(gtk_builder_get_object (data->dialog_edit_entry_ui,"comboboxPanel"));
    spinbuttonDays = GTK_SPIN_BUTTON(gtk_builder_get_object (data->dialog_edit_entry_ui,"spinbuttonDays"));
    sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"translationTreeView")));
    model = gtk_tree_view_get_model (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"translationTreeView")));
    treestore = GTK_TREE_STORE(model);
    if (!gtk_tree_selection_get_selected (sel, &model, &iter)) return;
    
    gtk_tree_model_get (model, &iter, 2, &entry, -1);
    
    gtk_entry_set_text(entryTranslationlang1,entry->word1);
    gtk_entry_set_text(entryTranslationlang2,entry->word2);
    gtk_entry_set_text(entryLanguageName1,entry->lang1name);
    gtk_entry_set_text(entryLanguageName2,entry->lang2name);
    gtk_entry_set_text(entryGroup,entry->groupname);
    gtk_spin_button_set_value(spinbuttonDays,(gdouble)entry->days);
    if (gtk_dialog_run (GTK_DIALOG(dialog))==GTK_RESPONSE_OK)
      {

      }
    gtk_widget_hide(dialog);
}

void main_window_onbtnDeleteEntry(GtkWidget *widget, gpointer user_data)
{
    g_print("... main_window_onbtnDeleteEntry\n");
}