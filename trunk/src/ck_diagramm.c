/**
 * ck_diagramm.c
 *
 * A GTK+ widget that implements a clock face
 *
 * (c) 2005, Davyd Madeley
 *
 * Authors:
 *   Davyd Madeley  <davyd@madeley.id.au>
 */

#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

#include "ck_diagramm.h"

G_DEFINE_TYPE (CkDiagramm, ck_diagramm, GTK_TYPE_DRAWING_AREA);

static gboolean ck_diagramm_expose (GtkWidget *ck_diagramm, GdkEventExpose *event);

static void ck_diagramm_class_init (CkDiagrammClass *class)
{
	GtkWidgetClass *widget_class;

	widget_class = GTK_WIDGET_CLASS (class);

	widget_class->expose_event = ck_diagramm_expose;
}

static void ck_diagramm_init (CkDiagramm *ck_diagramm)
{
}

static void draw (GtkWidget *ck_diagramm, cairo_t *cr)
{
	double x, y;
	double radius;
	int i;
	
	x = ck_diagramm->allocation.width / 2;
	y = ck_diagramm->allocation.height / 2;
	radius = MIN (ck_diagramm->allocation.width / 2,
		      ck_diagramm->allocation.height / 2) - 5;

	/* clock back */
	cairo_arc (cr, x, y, radius, 0, M_PI/180.0 * 20.0);
	cairo_line_to(cr,x,y);
	cairo_set_source_rgb (cr, 0, 1, 1);
	cairo_fill_preserve (cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_stroke (cr);
	/* clock ticks */
	for (i = 0; i < 12; i++)
	{
		int inset;
	
		cairo_save (cr); /* stack-pen-size */
		
		if (i % 3 == 0)
		{
			inset = 0.2 * radius;
		}
		else
		{
			inset = 0.1 * radius;
			cairo_set_line_width (cr, 0.5 *
					cairo_get_line_width (cr));
		}
		
		cairo_move_to (cr,
				x + (radius - inset) * cos (i * M_PI / 6),
				y + (radius - inset) * sin (i * M_PI / 6));
		cairo_line_to (cr,
				x + radius * cos (i * M_PI / 6),
				y + radius * sin (i * M_PI / 6));
		cairo_stroke (cr);
		cairo_restore (cr); /* stack-pen-size */
	}
}

static gboolean ck_diagramm_expose (GtkWidget *ck_diagramm, GdkEventExpose *event)
{
	cairo_t *cr;

	/* get a cairo_t */
	cr = gdk_cairo_create (ck_diagramm->window);

	cairo_rectangle (cr,
			event->area.x, event->area.y,
			event->area.width, event->area.height);
	cairo_clip (cr);
	
	draw (ck_diagramm, cr);

	cairo_destroy (cr);
       
	return FALSE;
}

GtkWidget *ck_diagramm_new (void)
{
	return g_object_new (CK_TYPE_DIAGRAMM, NULL);
}

