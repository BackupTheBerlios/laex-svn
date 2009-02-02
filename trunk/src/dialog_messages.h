/***************************************************************************
 *            dialog_messages.h
 *
 *  Tue Jan 13 15:42:23 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<berlios.de>
 ****************************************************************************/

#ifndef _DIALOG_MESSAGES_H
#define DIALOG_MESSAGES_H

#include <glib.h>
#include <gtk/gtk.h>

void dialog_message (gchar *message);
gint dialog_question(gchar *message);
gchar *dialog_input(gchar* title,gchar *message, gchar *templ); 
// title: title of Window
// message: Message
// templ: Template of String
// return: String or NULL (if Cancel)
// return has to be freed

#endif /* DIALOG_MESSAGES_H */
