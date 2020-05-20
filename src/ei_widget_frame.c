#include "ei_widget_frame.h"


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
        int i, j, k;
        ei_linked_point_t		points[4];
        int coord_x[] = {widget->screen_location.top_left.x, widget->screen_location.top_left.x + widget->screen_location.size.height};
        int coord_y[] = {widget->screen_location.top_left.y, widget->screen_location.top_left.y + widget->screen_location.size.width};
        // Define the polygon vertices.
        for (i = 0, k = 0; i < 2 && k < 4; i++) {
                printf("1er for");
                for (j=0; j < 2; j++){
                        points[k].point.x	= coord_x[i];
                        points[k].point.y	= coord_y[j];
                        if (k < 3)
                                points[k].next	= &(points[i+1]);
                        else
                                points[k].next	= NULL;
                        k++;
                        printf("2eme for");
                }
        }
        // lock the surface for drawing
        hw_surface_lock(ei_app_root_surface());

        // draw the polygon
        ei_draw_polygon(ei_app_root_surface(), points, frame->color, &(widget->screen_location));
        /*// fill the surface with the specified color
        ei_fill(ei_app_root_surface(), &(frame->color), &(widget->screen_location));*/

        // unlock the surface and update the screen
        hw_surface_unlock(ei_app_root_surface());
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