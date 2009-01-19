#include "main_window.h"
#include "statistics.h"
#include "word_preview.h"
#include "word_practise.h"
#include "select_words.h"
#include "dialog_edit_entry.h"
#include "data.h"
#include <string.h>

void main_window_init()
{
}

void main_window_onConnect(GtkWidget *main_window, gpointer user_data)
{
    cDATA* data;
    data = (cDATA*) user_data;
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"main_window")),"destroy", G_CALLBACK(main_window_onQuit),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnSearch")),"clicked", G_CALLBACK(main_window_onSearch),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toggleProperties")),"toggled", G_CALLBACK(main_window_ontoggleProperties),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"translationTreeView")),"cursor-changed", G_CALLBACK(main_window_ontranslationTreeViewCursorChanged),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnAddGroup")),"clicked", G_CALLBACK(main_window_onbtnAddGroup),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnDeleteGroup")),"clicked", G_CALLBACK(main_window_onbtnDeleteGroup),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnNewEntry")),"clicked", G_CALLBACK(main_window_onbtnNewEntry),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnEditEntry")),"clicked", G_CALLBACK(main_window_onbtnEditEntry),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnDeleteEntry")),"clicked", G_CALLBACK(main_window_onbtnDeleteEntry),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonTraining")),"clicked", G_CALLBACK(main_window_ontoolbuttonSelectWordsInit),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonPreferences")),"clicked", G_CALLBACK(main_window_ontoolbuttonPreferences),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonHelp")),"clicked", G_CALLBACK(main_window_ontoolbuttonHelp),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonabout")),"clicked", G_CALLBACK(main_window_ontoolbuttonabout),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonDictionary1")),"clicked", G_CALLBACK(main_window_ontoolbuttonDictionary),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonSelectWords1")),"clicked", G_CALLBACK(main_window_ontoolbuttonSelectWords),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPreview1")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPreview),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPractise1")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPractise),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonDictionary2")),"clicked", G_CALLBACK(main_window_ontoolbuttonDictionary),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonStatistics")),"clicked", G_CALLBACK(main_window_ontoolbuttonStatistics),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPreview2")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPreview),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPractise2")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPractise),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup")),"changed", G_CALLBACK(main_window_oncomboboxSelectGroup),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"comboboxSelectWords")),"changed", G_CALLBACK(main_window_oncomboboxSelectWords),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"buttonToPanel1")),"clicked", G_CALLBACK(main_window_onbuttonToPanel1),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"buttonToPanel0")),"clicked", G_CALLBACK(main_window_onbuttonToPanel0),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnWordPreviewNext")),"clicked", G_CALLBACK(main_window_onbtnWordPreviewNext),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPreviewBack")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPreviewBack),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnWordPractiseNext")),"clicked", G_CALLBACK(main_window_onbtnWordPractiseNext),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"toolbuttonWordPractiseBack")),"clicked", G_CALLBACK(main_window_ontoolbuttonWordPractiseBack),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnSelectWordsSelectAll")),"clicked", G_CALLBACK(main_window_onbtnSelectWordsSelectAll),user_data);	
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnSelectWordsToPanel1")),"clicked", G_CALLBACK(main_window_onbtnSelectWordsToPanel1),user_data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object (data->main_window_ui,"btnSelectWordsToPanel0")),"clicked", G_CALLBACK(main_window_onbtnSelectWordsToPanel0),user_data);

}

void main_window_run(gpointer user_data)
{ 
 cDATA* data;
 GtkWindow *main_window;
 data = (cDATA*) user_data;
 data->main_window_ui = gtk_builder_new ();
 gtk_builder_add_from_file(data->main_window_ui,"main_window.ui",NULL);
 main_window = GTK_WINDOW(gtk_builder_get_object (data->main_window_ui,"main_window"));
 gtk_notebook_set_show_tabs (GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),FALSE);
 
 gtk_widget_show (GTK_WIDGET(main_window));
 main_window_onConnect(GTK_WIDGET(main_window),user_data);
 main_window_init_translationTreeView(user_data);
 main_window_init_treeviewGroup(user_data);
 main_window_init_comboboxSelectWords(user_data);
 
 // dialog_edit_entry:
 data->dialog_edit_entry_ui = gtk_builder_new ();
 gtk_builder_add_from_file(data->dialog_edit_entry_ui,"dialogEditEntry.ui",NULL);

 main_window_init_comboboxPanel(data);
 main_window_init_treeviewSelectWords(data);
 
 // dialog_start_Training:
  data->dialog_start_training_ui = gtk_builder_new ();
  gtk_builder_add_from_file(data->dialog_start_training_ui,"dialogStartTraining.ui",NULL);

}

void main_window_delete(gpointer user_data)
{
    cDATA* data;
    data = (cDATA*) user_data;
    g_object_unref(G_OBJECT(data->main_window_ui));
    g_object_unref(G_OBJECT(data->dialog_edit_entry_ui));
    g_object_unref(G_OBJECT(data->dialog_start_training_ui));
    data->main_window_ui=NULL;
    data->dialog_edit_entry_ui=NULL;
}

void main_window_init_translationTreeView(gpointer user_data)
{
   cDATA *data;
   GtkTreeViewColumn   *col;
   GtkCellRenderer     *renderer;
   GtkTreeStore		   *treestore;
   GtkTreeView		   *view;
   GtkTreeModel		   *model;
   
   GtkRequisition size;
   //gtk_widget_size_request(widget,&size);
   data = (cDATA*) user_data;
   view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"translationTreeView"));
   gtk_widget_get_child_requisition(GTK_WIDGET(view),&size);
   col = gtk_tree_view_column_new();
   gtk_tree_view_column_set_title(col, data->lang2name);
   gtk_tree_view_append_column(view, col);
   renderer = gtk_cell_renderer_text_new();
  // pack cell renderer into tree view column
   gtk_tree_view_column_pack_start(col, renderer, TRUE);
   gtk_tree_view_column_set_sizing(col,GTK_TREE_VIEW_COLUMN_FIXED);
   gtk_tree_view_column_set_fixed_width(col,380);
   gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN (col), TRUE);
  // connect 'text' property of the cell renderer to
  //  model column that contains the first name
   gtk_tree_view_column_add_attribute(col, renderer, "text", 0);
   col = gtk_tree_view_column_new();
   gtk_tree_view_column_set_title(col, data->lang1name);
  // pack tree view column into tree view
  gtk_tree_view_column_set_fixed_width(col,380);
  gtk_tree_view_append_column(view, col);
  renderer = gtk_cell_renderer_text_new();
  // pack cell renderer into tree view column
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  //gtk_tree_view_column_set_sizing(col,GTK_TREE_VIEW_COLUMN_FIXED);
  // connect 'text' property of the cell renderer to
   //  model column that contains the first name
  gtk_tree_view_column_add_attribute(col, renderer, "text", 1);
  treestore = GTK_TREE_STORE(gtk_tree_view_get_model(view));
    if (treestore==NULL)
      {
       treestore = gtk_tree_store_new(3,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_POINTER);
	   model = GTK_TREE_MODEL(treestore);
       gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
                                  
       g_object_unref (model);
       }
   
	gtk_tree_store_clear(treestore);
  
}

void main_window_init_treeviewGroup(gpointer user_data)
{
    cDATA *data;
    GtkTreeStore *treestore;
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
  
    data = (cDATA*) (user_data);    
    renderer = gtk_cell_renderer_toggle_new();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")),
                                                         -1,
                                                         "Choice",
                                                         renderer,
                                                         "active",0,NULL);
    g_object_set(renderer,"activatable",TRUE,NULL);
    g_signal_connect(renderer,"toggled", G_CALLBACK(main_window_ontreeviewGroupChoice),user_data);
    
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "Group");
    gtk_tree_view_append_column(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")), col);
   
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "text", 1);
    g_object_set(renderer,"editable",TRUE,NULL);
    g_signal_connect(renderer, "edited", (GCallback) main_window_ontreeviewGroupEdited, user_data);
    
    treestore = gtk_tree_store_new(2,
                                 G_TYPE_BOOLEAN,
                                 G_TYPE_STRING);

     gtk_tree_view_set_model(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")), GTK_TREE_MODEL(treestore));
     g_object_unref(GTK_TREE_MODEL(treestore)); /* destroy model automatically with view */
     main_window_Show_treeviewGroup(user_data);
}


void main_window_Show_treeviewGroup(gpointer user_data)
{
     GtkTreeView *view;
     GtkTreeStore *treestore;
     cDATA *data;
     GtkTreeIter toplevel;
     data = (cDATA*) (user_data);
     int i;
     cENTRY *entry;
     view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup"));	
     treestore = GTK_TREE_STORE(gtk_tree_view_get_model(view));
     if (treestore==NULL) return;
     
     for (i=0;i!=(int)data->grouplist->len;i++)
      {
         free(g_array_index (data->grouplist, char*, i));
       }
      g_array_free(data->grouplist,TRUE);
     data->grouplist = g_array_new(TRUE,FALSE,sizeof(char*));
     for (i=0;i!=(int)data->cwordlist->len;i++)
      {
         entry=g_array_index (data->cwordlist, cENTRY*, i),
         cdata_addgrouptolist(data,entry->groupname);      
       }
     
     
     
     gtk_tree_store_clear(treestore);
     for (i=0;i!=(int)data->grouplist->len;i++)
      {
         gtk_tree_store_append(treestore, &toplevel, NULL);
         gtk_tree_store_set(treestore, &toplevel,
                                0, FALSE,
                                1, g_array_index (data->grouplist, char*, i),
                                -1);
       }
}




void main_window_onQuit (GtkWidget *widget, gpointer user_data)
{
    g_print("... main_window_onQuit\n");
    gtk_main_quit();
}

void main_window_onSearch (GtkWidget *widget, gpointer user_data)
{
    GtkTreeView *view;
    GtkTreeStore *treestore;
    GtkTreeModel *model;
    GtkTreeIter toplevel, child;
    cDATA *data;
    cENTRY *entry;
    char *word1uppercase,*word2uppercase;
    char *word1part,*word2part;
    char *word,*word2;
    int i,i2,i3;
    
    g_print("... main_window_onSearch\n");
    data = (cDATA*) (user_data);
	view = GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"translationTreeView"));	
	treestore = GTK_TREE_STORE(gtk_tree_view_get_model(view));
    if (treestore==NULL)
      {
       treestore = gtk_tree_store_new(3,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_POINTER);
       model = GTK_TREE_MODEL(treestore);
       gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
                                  
       g_object_unref (model);
       }
   
	gtk_tree_store_clear(treestore);
                                 
    
      
  
    i2=0;
    word2 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui, "comboboxentryWord")));
    word = (char*)malloc(strlen(word2)+1);
    UpperCase(word,word2);    
    
    i2=0;
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
          entry = g_array_index (data->cwordlist, cENTRY*, i);
          word1uppercase = (char *) malloc(strlen(entry->word1)+1);
          word2uppercase = (char *) malloc(strlen(entry->word2)+1);
          UpperCase(word1uppercase,entry->word1);
          UpperCase(word2uppercase,entry->word2);
          if ((strstr(word1uppercase, word)!=NULL) || (strstr(word2uppercase, word)!=NULL))
             {
                i2++;
                if (i2 < 100)
			    {
                    i3=0;
                    word1part = (char *) malloc(strlen(entry->word1)+1);
                    word2part = (char *) malloc(strlen(entry->word2)+1);
                    while (GetStringColumn(word1part,entry->word1,"|",i3)==0)
                        {
                            if (GetStringColumn(word2part,entry->word2,"|",i3)!=0) break;
                            if (i3==0)
                              {
                                gtk_tree_store_append(treestore, &toplevel, NULL);
                                gtk_tree_store_set(treestore, &toplevel,
                                0, word1part,
                                1, word2part, 
                                2,entry,
                                -1);
                                //gtk_tree_view_column_set_sort_column_id (treestore,i3)
                              } else
                              {
                                gtk_tree_store_append(treestore, &child, &toplevel);
                                gtk_tree_store_set(treestore, &child,
                                0, word1part,
                                1, word2part, 
                                2, entry,
                                -1);
                              }
                           i3++;
                        } //while
                    
                    free(word1part);
                    free(word2part);
                 }//if (i2 < 100)
             }
          free(word1uppercase);
          free(word2uppercase);
      }
  }

void main_window_ontoggleProperties (GtkWidget *widget, gpointer user_data)
{
    cDATA *data;
    g_print("... main_window_ontoggleProperties\n");
    data = (cDATA*) user_data;
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget))==TRUE)
      {
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"frameGroup")));
            gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"alignmentEditWords")));
            
      } else
      {
            gtk_widget_hide(GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"frameGroup")));
            gtk_widget_show(GTK_WIDGET(gtk_builder_get_object (data->main_window_ui,"alignmentEditWords")));
      }
      
}

void main_window_ontreeviewGroupChoice (GtkCellRendererToggle *cell,gchar *path_string,gpointer user_data)
{
    g_print("... main_window_ontreeviewGroupChoice\n");
    GtkTreeIter  iter;
    cDATA *data;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
    gboolean enabled;
    GtkTreeModel *model;
    GtkTreeSelection* sel;
    cENTRY *entry;
    char *Sges,*S;
    
    data = (cDATA*) user_data;
    model = gtk_tree_view_get_model (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")));
     
         
    gtk_tree_model_get_iter (model, &iter, path);
    gtk_tree_model_get (model, &iter, 0, &enabled, -1);
    enabled ^= 1;
	gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
                                0, enabled,
                                -1);
    gtk_tree_path_free (path);
    
    
     if (gtk_tree_model_get_iter_first (model,&iter)== FALSE)
			      {
                    return;
                   }
			    gtk_tree_model_get (model, &iter, 0, &enabled, -1);
			    gtk_tree_model_get (model,&iter,1,&S,-1);
			    Sges=NULL;
			    while (1)
			    {
                               if (enabled==TRUE)
                                  {
                                    if (Sges==NULL)
                                    {
                                      Sges=(char*)malloc(strlen(S)+1);
                                      strcpy(Sges,S);
                                    } else
                                    {
                                      Sges=(char*)realloc(Sges,strlen(Sges)+strlen(S)+2);   
                                      strcat(Sges,"|");
                                      strcat(Sges,S);
                                    }
                        
                                  }
                                if (gtk_tree_model_iter_next (model,&iter)==FALSE)
                                  {
                                     break;
                                  }
                   
                                gtk_tree_model_get (model, &iter,0, &enabled, -1);
                                gtk_tree_model_get (model,&iter,1,&S,-1);
                             }
                 
                    sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"translationTreeView")));
                    if (gtk_tree_selection_get_selected (sel, &model, &iter))
                       {
                          gtk_tree_model_get (model, &iter, 2, &entry, -1);
                          free((void*)entry->groupname);
                          entry->groupname=Sges;
                       }
}



void main_window_ontranslationTreeViewCursorChanged(GtkTreeView *tree_view,gpointer user_data)
{
    GtkTreeSelection* sel;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *treeviewGroup;
    GtkTreeModel *modelGroup;
    GtkTreeIter iterGroup;
    cENTRY *entry;
    char *S;
    cDATA* data;
    
    g_print("... main_window_ontranslationTreeViewCursorChanged\n");
    
    data = (cDATA*) user_data;
    treeviewGroup=GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup"));
    modelGroup = gtk_tree_view_get_model(treeviewGroup);
    
    sel = gtk_tree_view_get_selection(tree_view);
    if (gtk_tree_selection_get_selected (sel, &model, &iter))
        {
                gtk_tree_model_get (model, &iter, 2, &entry, -1);
                
			    if (gtk_tree_model_get_iter_first (modelGroup,&iterGroup)== FALSE)
			      {
                    return;
                   }
			    gtk_tree_model_get (modelGroup, &iterGroup, 1, &S, -1);
			    while (1)
			    {
                   gtk_tree_store_set(GTK_TREE_STORE(modelGroup), &iterGroup,
                                0, centry_groupexist(entry,S),
                                -1);
                   if (gtk_tree_model_iter_next (modelGroup,&iterGroup)==FALSE)
                     {
                        break;
                     }
                   gtk_tree_model_get (modelGroup, &iterGroup, 1, &S, -1);
                 }
        }
}

void main_window_ontreeviewGroupEdited(GtkCellRendererText *cell,gchar *path_string,gchar *new_text,gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreePath *path; 
    char *oldText,*S;
    int i;
    cDATA *data;
    cENTRY *entry;
    g_print("... main_window_ontreeviewGroupEdited\n");
    data = (cDATA*) user_data;
    model = gtk_tree_view_get_model (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")));
    path = gtk_tree_path_new_from_string (path_string);
    gtk_tree_model_get_iter (model, &iter, path);
    
    gtk_tree_model_get (model, &iter, 1, &oldText, -1);
    
    
    
    
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
         entry = g_array_index (data->cwordlist, cENTRY*, i);
         centry_groupchange(entry,oldText,new_text);
      }
    for (i=0;i!=(int)data->grouplist->len;i++)
      {
         S = g_array_index (data->grouplist, char*, i);
         if (strcmp(S,oldText)==0)
           {
             free(S);
             S=(char*)malloc(strlen(new_text)+1);
             strcpy(S,new_text);
           }
         
      }
    
    free(oldText);
    
    gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
                                1, new_text,
                                -1);

    gtk_tree_path_free (path);
}



void main_window_onbtnAddGroup(GtkWidget *widget, gpointer user_data)
{
     GtkTreeModel *model;
     GtkTreeIter iter;
     GtkTreeStore *treestore;
     char *S;
     cDATA *data;
     g_print("... main_window_onbtnAddGroup\n");
     data = (cDATA*) user_data;
     model = gtk_tree_view_get_model (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")));
     treestore = GTK_TREE_STORE(model);

     S = (char*) malloc(strlen(_("New Group"))+1);
     strcpy(S,_("New Group"));
     g_array_append_val(data->grouplist,S);

     gtk_tree_store_append(treestore, &iter, NULL);    
     gtk_tree_store_set(treestore, &iter,
                                0, FALSE,
                                1, S,
                                -1);
}

void main_window_onbtnDeleteGroup(GtkWidget *widget, gpointer user_data)
{
    cDATA *data;
    int i;
    GtkTreeSelection* sel;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeStore *treestore;
    char *group;
    cENTRY *entry;
    g_print("... main_window_onbtnDeleteGroup\n");
    data = (cDATA*) user_data;
    sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")));
    model = gtk_tree_view_get_model (GTK_TREE_VIEW(gtk_builder_get_object (data->main_window_ui,"treeviewGroup")));
    treestore = GTK_TREE_STORE(model);
    if (gtk_tree_selection_get_selected (sel, &model, &iter))
        {
            gtk_tree_model_get (model, &iter, 1, &group, -1);
            g_print("... delete group %s!\n",group);
            for (i=0;i!=(int)data->cwordlist->len;i++)
              {
                 entry = g_array_index (data->cwordlist, cENTRY*, i);
                 centry_groupdelete(entry,group);
              } 
            gtk_tree_store_remove(treestore,&iter);
         }
}



void main_window_ontoolbuttonDictionary(GtkWidget *widget, gpointer user_data)
{
    cDATA *data;
    g_print("... main_window_ontoolbuttonDictionary\n");
    data = (cDATA*) user_data;
    gtk_notebook_set_current_page(GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),0);
}

void main_window_ontoolbuttonPreferences(GtkWidget *widget, gpointer user_data)
{
    g_print("... main_window_ontoolbuttonPreferences\n");
}

void main_window_ontoolbuttonHelp(GtkWidget *widget, gpointer user_data)
{
    g_print("... main_window_ontoolbuttonHelp\n");
}
void main_window_ontoolbuttonabout(GtkWidget *widget, gpointer user_data)
{
    cDATA *data;
    g_print("... main_window_ontoolbuttonabout\n");
    data = (cDATA*) user_data;
    gtk_show_about_dialog (GTK_WINDOW(gtk_builder_get_object (data->main_window_ui,"main_window")),
                       "program-name", "Language Explorer",
                       "title", _("About Language Explorer"),
                       "version","0.1",
                       "website","http://laex.berlios.de/",
                       "copyright","Copyright © 2009 Christian Klein",
                       NULL);
}
