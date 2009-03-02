/***************************************************************************
 *            statistics.c
 *
 *  Tue Jan 13 15:52:01 2009
 *  Copyright  2009  chrikle
 *  <chrikle@<host>>
 ****************************************************************************/

#include "statistics.h"
#include "data.h"
#include "centry.h"
#include "main_window.h"
#include "ck_diagramm.h"

void main_window_ontoolbuttonStatistics(GtkWidget *widget, gpointer user_data)
{
    GtkLabel *labelCount;
    GtkLabel *(labelWords[4]);//Panel 1..4 -> 0..3
    GtkLabel *(labelPercent[4]);//Panel 1..4 -> 0..3
    cDATA* data;
    cENTRY *entry;
    int i;
    unsigned int countofGroup;
    unsigned int countofP1to4;
    unsigned int CountWords[4];
    unsigned int PercentWords[4];
    char S[100];
    
    g_print("... main_window_ontoolbuttonStatistics\n");
    data = (cDATA*) user_data;
    labelCount = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelCount"));
    labelWords[0] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel1Words"));
    labelWords[1] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel2Words"));
    labelWords[2] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel3Words"));
    labelWords[3] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel4Words"));
    labelPercent[0] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel1Per"));
    labelPercent[1] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel2Per"));
    labelPercent[2] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel3Per"));
    labelPercent[3] = GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelPanel4Per"));
    if (data->traingroup==NULL) {data->traingroup=gtk_combo_box_get_active_text(GTK_COMBO_BOX(gtk_builder_get_object (data->main_window_ui,"comboboxSelectGroup")));}
    sprintf(S,"Statistic of %s:",data->traingroup);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (data->main_window_ui,"labelStatisticsGroup")),S);
    countofGroup=0;
    countofP1to4=0;
    for (i=0;i!=4;i++)
      {
            CountWords[i]=0;
            PercentWords[i]=0;
      }
    
    for (i=0;i!=(int)data->cwordlist->len;i++)
      {
         entry = g_array_index (data->cwordlist, cENTRY*, i);
         if (centry_groupexist(entry,data->traingroup)==TRUE)
            {
               countofGroup++;
               if (entry->panel>0)
                 {
                    countofP1to4++;
                    CountWords[entry->panel-1]++;
                 }
            }
      }
    if (countofGroup>0)
      {
            for (i=0;i!=4;i++)
                {
                    PercentWords[i]=(unsigned int)((double)CountWords[i]*100.5/(double)countofP1to4++);
                }
      }
      
    sprintf(S,"%d",countofGroup);
    gtk_label_set_text(labelCount,S);
    for (i=0;i!=4;i++)
      {  
            sprintf(S,"%d",CountWords[i]);
            gtk_label_set_text(labelWords[i],S);
            sprintf(S,"%d%%",PercentWords[i]);
            gtk_label_set_text(labelPercent[i],S);
      }
    gtk_notebook_set_current_page(GTK_NOTEBOOK(gtk_builder_get_object (data->main_window_ui,"notebookmain")),1);
}
