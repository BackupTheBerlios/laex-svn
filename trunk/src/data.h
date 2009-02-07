#ifndef _DATA_H
#define _DATA_H
#include <stdio.h>
#include <glib.h>
#include <gtk/gtk.h>
#include "cstrman.h"
#include "centry.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
// DIRS:
#define UI_PATH PACKAGE_DATA_DIR"/"PACKAGE"/ui/"
#define ICON_PATH PACKAGE_DATA_DIR"/"PACKAGE"/pixmaps/"
#define DOCHTML_PATH PACKAGE_PREFIX_DIR"/doc/"PACKAGE"/html/"
#define LAEX_VERSION VERSION
#else
#define UI_PATH "ui/"
#define ICON_PATH "icons/"
#define DOCHTML_PATH "doc/"
#define LAEX_VERSION "0.8.1"
#endif

#define _(x) x


typedef struct {  GtkWidget *menu;
                  GtkWidget *new_item;
                  GtkWidget *edit_item;
                  GtkWidget *delete_item; 
	        } struct_translationViewPopUp;
	        
typedef struct {  GtkWidget *menu;
                  GtkWidget *new_item;
                  GtkWidget *edit_item;
                  GtkWidget *delete_item; 
	        } struct_GroupPopUp;


typedef struct {    
                    char *configdir;
                    char *dictfile;
                    int paneldays[5];
	            GArray *grouplist;
	            GArray *cwordlist;
	            GArray *trainlist;
	            signed int trainindex;
	            char *traingroup;
		    char *lang1name,*lang2name;
		    gboolean traindirection;
	            gboolean trainasked;
	            struct_translationViewPopUp translationViewPopUp;
	            struct_GroupPopUp groupPopUp;
	            GtkBuilder *main_window_ui;
	            GtkBuilder *dialog_edit_entry_ui;
	            GtkBuilder *dialog_start_training_ui;
	            GtkBuilder *assistant_import_ui;
	            } cDATA;


cDATA* cdata_init();

void cdata_delete(cDATA* data);

void cdata_loaddicfile(cDATA *data,char *filename, char *_lang1, char *_lang2, char* _group,gboolean _append);
//void cdata_saveXMLWordList(cDATA *data, char *filename);

void cdata_addgrouptolist(cDATA *data,char *group);


#endif /*_DATA_H*/
