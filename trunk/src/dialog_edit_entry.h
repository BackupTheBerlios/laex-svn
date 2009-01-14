/***************************************************************************
 *            dialog_edit_entry.h
 *
 *  Tue Jan 13 15:42:23 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#ifndef _DIALOG_EDIT_ENTRY_H
#define DIALOG_EDIT_ENTRY_H

#include <glib.h>
#include <gtk/gtk.h>

void main_window_init_comboboxPanel(gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnNewEntry(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnEditEntry(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnDeleteEntry(GtkWidget *widget, gpointer user_data);



#endif /* DIALOG_EDIT_ENTRY_H */

