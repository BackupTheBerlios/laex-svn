#ifndef _DATA_H
#define _DATA_H
#include <stdio.h>
#include <glib.h>
#include <gtk/gtk.h>
#include "cstrman.h"
#include "centry.h"

#define _(x) x

typedef struct {char *dictfile;
                    int paneldays[5];
	            GArray *grouplist;
	            GArray *cwordlist;
	            GArray *trainlist;
	            signed int trainindex;
	            char *traingroup;
				char *lang1name,*lang2name;
				gboolean traindirection;
	            gboolean trainasked;
	            GtkBuilder *main_window_ui;
	            GtkBuilder *dialog_edit_entry_ui;
	            GtkBuilder *dialog_start_training_ui;
	            } cDATA;


cDATA* cdata_init();

void cdata_delete(cDATA* data);

void cdata_loaddicfile(cDATA *data);
void cdata_saveXMLWordList(cDATA *data, char *filename);

void cdata_addgrouptolist(cDATA *data,char *group);


#endif /*_DATA_H*/
