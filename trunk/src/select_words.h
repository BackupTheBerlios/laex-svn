#ifndef _SELECT_WORDS_H
#define SELECT_WORDS_H

#include <gtk/gtk.h>

void main_window_init_comboboxSelectWords(gpointer user_data);
void main_window_init_treeviewSelectWords(gpointer user_data);
void main_window_change_treeviewSelectWords(gpointer user_data);
void main_window_copy_selected_to_Panel1(GtkTreeModel *model,GtkTreePath *path, GtkTreeIter *iter, gpointer data);
void main_window_copy_selected_to_Panel0(GtkTreeModel *model,GtkTreePath *path, GtkTreeIter *iter, gpointer data);

G_MODULE_EXPORT void main_window_oncomboboxSelectGroup(GtkComboBox *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_oncomboboxSelectWords(GtkComboBox *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_oncomboboxSelectWords(GtkComboBox *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbuttonToPanel1(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbuttonToPanel0(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonSelectWords(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonSelectWordsInit(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnSelectWordsSelectAll(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnSelectWordsToPanel1(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnSelectWordsToPanel0(GtkWidget *widget, gpointer user_data);


#endif /* SELECT_WORDS_H */

