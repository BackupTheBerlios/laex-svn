#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>


void main_window_init();
void main_window_run(gpointer user_data);
void main_window_delete(gpointer user_data);


void main_window_onConnect(GtkWidget *main_window, gpointer user_data);
void main_window_init_translationTreeView(gpointer user_data);
void main_window_init_treeviewGroup(gpointer user_data);
void main_window_Show_treeviewGroup(gpointer user_data);



G_MODULE_EXPORT void main_window_onQuit (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onSearch (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoggleProperties (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontreeviewGroupChoice (GtkCellRendererToggle *cell,gchar *path_string,gpointer user_data);
G_MODULE_EXPORT void main_window_ontreeviewGroupEdited(GtkCellRendererText *cell,gchar *path_string,gchar *new_text,gpointer user_data);
G_MODULE_EXPORT void main_window_ontranslationTreeViewCursorChanged(GtkTreeView *tree_view,gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnAddGroup(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnDeleteGroup(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonPreferences(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonHelp(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonabout(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonDictionary(GtkWidget *widget, gpointer user_data);




#endif /*_MAIN_WINDOW_H*/
