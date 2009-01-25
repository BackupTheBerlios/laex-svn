/***************************************************************************
 *            dialog_edit_entry.h
 *
 *  Tue Jan 13 15:42:23 2009
 *  Copyright  2009 Christian Klein
 *  <chrikle@berlios.de>
 ****************************************************************************/

#ifndef _ASSISTANT_IMPORT_H
#define _ASSISTANT_IMPORT_H

#include <glib.h>
#include <gtk/gtk.h>
#include "data.h"

void assistant_import_init(gpointer user_data);
void assistant_import_run(gpointer user_data);
void assistant_import_onConnect(GtkWidget *assistant_import, gpointer user_data);
void assistant_import_delete(gpointer user_data);

G_MODULE_EXPORT void assistant_import_onQuit (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void assistant_import_onfilechooserbuttonImportFile (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void assistant_import_onapllypressed (GtkWidget *widget, gpointer user_data);
#endif /* _ASSISTANT_IMPORT_H */
