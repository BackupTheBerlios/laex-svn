/**
 * ck_diagramm.h
 *
 * A GTK+ widget that impements a diagramm
 *
 * (c) 2009, Christian Klein
 *
 * Authors:
 *   Christian Klein  <chrikle@berlios.de>
 */

#ifndef __CK_DIAGRAMM_H__
#define __CK_DIAGRAMM_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CK_TYPE_DIAGRAMM                (ck_diagramm_get_type ())
#define CK_DIAGRAMM(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CK_TYPE_DIAGRAMM, CkDiagramm))
#define CK_DIAGRAMM_CLASS(obj)	        (G_TYPE_CHECK_CLASS_CAST ((obj), CK_DIAGRAMM, CkDiagrammClass))
#define CK_IS_DIAGRAMM(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CK_DIAGRAMM))
#define CK_IS_DIAGRAMM_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE ((obj), CK_TYPE_DIAGRAMM))
#define CK_DIAGRAMM_GET_CLASSS	        (G_TYPE_INSTANCE_GET_CLASS ((obj), CK_TYPE_DIAGRAMM, CkDiagrammClass))




typedef struct _CkDiagramm		CkDiagramm;
typedef struct _CkDiagrammClass	        CkDiagrammClass;

struct _CkDiagramm
{
	GtkDrawingArea parent;

	/* < private > */
};

struct _CkDiagrammClass
{
	GtkDrawingAreaClass parent_class;
};

GtkWidget *ck_diagramm_new (void);

G_END_DECLS

#endif

