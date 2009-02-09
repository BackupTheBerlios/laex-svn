/***************************************************************************
 *            dialog_edit_entry.h
 *
 *  Tue Jan 13 15:42:23 2009
 *  Copyright  2009 Christian Klein
 *  <chrikle@berlios.de>
 ****************************************************************************/

#ifndef _ASSISTANT_EXPORT_H
#define _ASSISTANT_EXPORT_H

#include <glib.h>
#include <gtk/gtk.h>
#include "data.h"

void assistant_export_init(gpointer user_data);
void assistant_export_run(gpointer user_data);
void assistant_export_onConnect(GtkWidget *assistant_export, gpointer user_data);
void assistant_export_delete(gpointer user_data);

G_MODULE_EXPORT void assistant_export_onQuit (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void assistant_export_onfilechooserbuttonExportFile (GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void assistant_export_onapllypressed (GtkWidget *widget, gpointer user_data);
#endif /* _ASSISTANT_EXPORT_H */
