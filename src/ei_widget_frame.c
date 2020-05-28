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
void frame_drawfunc(ei_widget_t        *widget,
                    ei_surface_t	surface,
                    ei_surface_t	pick_surface,
                    ei_rect_t*		clipper){
        // declaration of the widget as a frame
        ei_frame_t* frame = (ei_frame_t*)widget;
        int coord_x[] = {widget->screen_location.top_left.x,
                         widget->screen_location.top_left.x + widget->screen_location.size.width};
        int coord_y[] = {widget->screen_location.top_left.y,
                         widget->screen_location.top_left.y + widget->screen_location.size.height};
        // Define the polygon vertices.
        ei_linked_point_t* points;
        points = rectangle(coord_x, coord_y, 0);
        // lock the surface for drawing
        hw_surface_lock(surface);
        // draw the polygon
        if (frame->relief != ei_relief_none) {
                draw_polygons_relief(widget, points, surface);
                free(points);
                points = rectangle(coord_x, coord_y, frame->border_width);
        }
        ei_draw_polygon(surface, points, frame->color, &(widget->screen_location));
        hw_surface_lock(pick_surface);
        ei_draw_polygon(pick_surface, points, *widget->pick_color, &(widget->screen_location));
        hw_surface_unlock(pick_surface);

        if (frame->text) {
                ei_point_t *where = malloc(sizeof(ei_point_t));
                int * width_txt = calloc(1, sizeof(int));
                int * height_txt = calloc(1, sizeof(int));
                hw_text_compute_size(frame->text, frame->text_font, width_txt, height_txt);
                where->x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 - *width_txt/2;
                where->y = widget->screen_location.top_left.y + widget->screen_location.size.height/2 - *height_txt/2;

                ei_rect_t * clipper_button_text = widget->content_rect;
                if(clipper_button_text->top_left.x + clipper_button_text->size.width > clipper->top_left.x + clipper->size.width)
                        clipper_button_text->size.width = clipper->top_left.x + clipper->size.width  - clipper_button_text->top_left.x;
                if(clipper_button_text->top_left.y + clipper_button_text->size.height > clipper->top_left.y + clipper->size.height)
                        clipper_button_text->size.height = clipper->top_left.y + clipper->size.height  - clipper_button_text->top_left.y;

                ei_draw_text(ei_app_root_surface(), where, frame->text,
                             frame->text_font, frame->text_color, clipper_button_text);
                free(width_txt);
                free(height_txt);
                free(where);
        }

        // unlock the surface and update the screen
        hw_surface_unlock(surface);
        hw_surface_update_rects(surface, NULL);
        free(points);
        if (widget->children_head) widget->children_head->wclass->drawfunc(widget->children_head, surface, pick_surface, widget->content_rect);
        if (widget->next_sibling) widget->next_sibling->wclass->drawfunc(widget->next_sibling, surface, pick_surface, clipper);
}

/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
void* frame_allocfunc(){
        return (void*) calloc(1, sizeof(ei_frame_t));
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
        free(frame->text);
        free(frame->img_rect);
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