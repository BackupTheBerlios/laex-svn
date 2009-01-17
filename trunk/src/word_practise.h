/***************************************************************************
 *            word_practise.h
 *
 *  Tue Jan 13 16:00:11 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

 
 #ifndef _WORD_PRACTISE_H
#define WORD_PRACTISE_H

#include <glib.h>
#include <gtk/gtk.h>
#include "data.h"

void main_window_WordPractiseShowNextWord(cDATA *data);
gboolean known(char *original, char* answered);

G_MODULE_EXPORT void main_window_ontoolbuttonWordPractise(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_onbtnWordPractiseNext(GtkWidget *widget, gpointer user_data);
G_MODULE_EXPORT void main_window_ontoolbuttonWordPractiseBack(GtkWidget *widget, gpointer user_data);

#endif /* WORD_PRACTISE_H */

