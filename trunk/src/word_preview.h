#ifndef _WORD_PREVIEW_H
#define WORD_PREVIEW_H

#include <gtk/gtk.h>


G_MODULE_EXPORT void main_window_onbtnWordPreviewNext(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonWordPreview(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonWordPreviewBack(GtkWidget *widget, gpointer user_data);

#endif /* WORD_PREVIEW_H */

