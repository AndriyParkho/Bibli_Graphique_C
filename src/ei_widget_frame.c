#include "ei_widget_frame.h"
#include <string.h>
#include <stdbool.h>
#include "ei_application.h"

/**
 * \brief	A function that draws frame.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	pick_surface	The surface used for picking (i.e. find the widget below the mouse pointer).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
void frame_drawfunc(ei_widget_t *widget){
        // declaration of the widget as a frame
        ei_frame_t* frame = (ei_frame_t*)widget;

        // lock the surface for drawing
        ei_surface_t draw_surface = hw_surface_create(ei_app_root_surface(), widget->requested_size, true);
        hw_surface_lock(draw_surface);

        // fill the surface with the specified color
        ei_fill(draw_surface, &(frame->color), &(widget->screen_location));

        // unlock the surface and update the screen
        hw_surface_unlock(draw_surface);
        hw_surface_update_rects(ei_app_root_surface(), NULL);
}

/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
void* frame_allocfunc(){
        return(calloc(1, sizeof(ei_frame_t)));
}

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
void frame_releasefunc(ei_frame_t* frame){
        free(frame);
}

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to initialize.
 */
void frame_setdefaultsfunc(ei_widget_t* widget){
    ei_frame_t* frame = (ei_frame_t*)widget;
    ei_color_t			white			= { 0xff, 0xff, 0xff, 0xff };
    ei_color_t          black           = {0x00,0x00,0x00,0xff};

    frame->color = ei_default_background_color;
    frame->border_width = 0;
    frame->relief = ei_relief_none;
    frame->text = NULL;
    frame->text_font = ei_default_font;
    frame->text_color = ei_font_default_color;
    frame->text_anchor = ei_anc_center;
    frame->img = NULL;
    frame->img_rect = NULL;
    frame->img_anchor = ei_anc_center;
}

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
void frame_geomnotifyfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}