#include "ei_widget_frame.h"
#include <stdlib.h>


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
        int i;
        ei_linked_point_t		points[4];
        int coord_x[] = {widget->screen_location.top_left.x, widget->screen_location.top_left.x + widget->screen_location.size.width};
        int coord_y[] = {widget->screen_location.top_left.y, widget->screen_location.top_left.y + widget->screen_location.size.height};
        // Define the polygon vertices.
        i=0;
        while (i!=4) {
                switch (i) {
                        case 0 : points[i].point.x = coord_x[0];
                                 points[i].point.y = coord_y[0];
                                 break;
                        case 1 : points[i].point.x = coord_x[1];
                                 points[i].point.y = coord_y[0];
                                 break;
                        case 2 : points[i].point.x = coord_x[1];
                                 points[i].point.y = coord_y[1];
                                 break;
                        case 3 : points[i].point.x = coord_x[0];
                                 points[i].point.y = coord_y[1];
                                 break;
                }
                if (i<3) points[i].next = &points[i+1];
                else points[i].next = NULL;
                i++;
        }
        // lock the surface for drawing
        hw_surface_lock(ei_app_root_surface());

        /*// fill the surface with the specified color
        ei_fill(ei_app_root_surface(), &(frame->color), &(widget->screen_location));*/

        // draw the polygon
        if (frame->relief != ei_relief_none) {
                int border_width = frame->border_width;
                int half_length = widget->screen_location.size.height / 2;
                ei_linked_point_t points_sup[5];
                ei_linked_point_t points_inf[5];
                ei_color_t dark_color = {frame->color.red - 30, frame->color.green - 30,
                                         frame->color.blue - 30, frame->color.alpha};
                ei_color_t light_color = {frame->color.red + 30, frame->color.green + 30,
                                          frame->color.blue + 30, frame->color.alpha};
                i = 0;
                while (i != 5) {
                        switch (i) {
                                case 0 :
                                case 1 :
                                        points_sup[i] = points[i];
                                        points_inf[i] = points[i + 1];
                                        break;
                                case 2 :
                                        points_sup[i].point.x = points[i].point.x - half_length;
                                        points_sup[i].point.y = points[i].point.y - half_length;
                                        points_inf[i] = points[i + 1];
                                        break;
                                case 3 :
                                        points_sup[i].point.x = points[i].point.x + half_length;
                                        points_sup[i].point.y = points[i].point.y - half_length;
                                        points_inf[i].point.x = points[i].point.x + half_length;
                                        points_inf[i].point.y = points[i].point.y - half_length;
                                        break;
                                case 4 :
                                        points_sup[i] = points[i - 1];
                                        points_inf[i].point.x = points[i - 2].point.x - half_length;
                                        points_inf[i].point.y = points[i - 2].point.y - half_length;
                                        break;
                        }
                        if (i < 4) points_sup[i].next = &points_sup[i + 1];
                        else points_sup[i].next = NULL;
                        if (i < 4) points_inf[i].next = &points_inf[i + 1];
                        else points_inf[i].next = NULL;
                        i++;
                }
                if (frame->relief == ei_relief_raised) {
                        ei_draw_polygon(ei_app_root_surface(), points_sup, light_color, &(widget->screen_location));
                        ei_draw_polygon(ei_app_root_surface(), points_inf, dark_color, &(widget->screen_location));
                } else { // cad frame->relief == ei_relief_sunken
                        ei_draw_polygon(ei_app_root_surface(), points_sup, dark_color, &(widget->screen_location));
                        ei_draw_polygon(ei_app_root_surface(), points_inf, light_color, &(widget->screen_location));
                }
                i = 0;
                while (i != 4) {
                        switch (i) {
                                case 0 :
                                        points[i].point.x = coord_x[0] + border_width;
                                        points[i].point.y = coord_y[0] + border_width;
                                        break;
                                case 1 :
                                        points[i].point.x = coord_x[1] - border_width;
                                        points[i].point.y = coord_y[0] + border_width;
                                        break;
                                case 2 :
                                        points[i].point.x = coord_x[1] - border_width;
                                        points[i].point.y = coord_y[1] - border_width;
                                        break;
                                case 3 :
                                        points[i].point.x = coord_x[0] + border_width;
                                        points[i].point.y = coord_y[1] - border_width;
                                        break;
                        }
                        if (i < 3) points[i].next = &points[i + 1];
                        else points[i].next = NULL;
                        i++;
                }
        }
        ei_draw_polygon(ei_app_root_surface(), points, frame->color, &(widget->screen_location));

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
        return(calloc(1, sizeof(ei_frame_t*)));
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