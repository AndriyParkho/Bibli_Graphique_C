/*
 * Fonctions propres au widget button
 */

#include "ei_widget_button.h"
#include "ei_widget_frame.h"


/**
 * \brief	A function that draws button.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	pick_surface	The surface used for picking (i.e. find the widget below the mouse pointer).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
void button_drawfunc(ei_widget_t        *widget,
                     ei_surface_t	surface,
                     ei_surface_t	pick_surface,
                     ei_rect_t*		clipper){
        ei_frame_t* frame = (ei_frame_t*)widget;
        ei_button_t* button = (ei_button_t*)widget;
        ei_linked_point_t* points;
        ei_color_t dark_color = color_variation(frame, -30);
        ei_color_t light_color = color_variation(frame, 30);
        ei_rect_t new_rect;

        hw_surface_lock(surface);

        if (button->frame.relief == ei_relief_raised) {
                //Partie haute
                points = rounded_frame(button->frame.widget.screen_location, button->corner_radius, 2);
                ei_draw_polygon(surface, points, light_color, &(widget->screen_location));
                free_points(points);

                //Partie basse
                points = rounded_frame(button->frame.widget.screen_location, button->corner_radius, 1);
                ei_draw_polygon(surface, points, dark_color, &(widget->screen_location));
                free_points(points);
        }
        else if (button->frame.relief == ei_relief_sunken) {
                //Partie haute
                points = rounded_frame(button->frame.widget.screen_location, button->corner_radius, 2);
                ei_draw_polygon(surface, points, dark_color, &(widget->screen_location));
                free_points(points);

                //Partie basse
                points = rounded_frame(button->frame.widget.screen_location, button->corner_radius, 1);
                ei_draw_polygon(surface, points, light_color, &(widget->screen_location));
                free_points(points);
        }

        //Totalité
        new_rect = widget->screen_location;
        new_rect.top_left.x += button->frame.border_width;
        new_rect.top_left.y += button->frame.border_width;
        new_rect.size.width -= 2*button->frame.border_width;
        new_rect.size.height -= 2*button->frame.border_width;
        points = rounded_frame(new_rect, button->corner_radius,0);
        ei_draw_polygon(surface, points, button->frame.color, &new_rect);
        free_points(points);
        // Dessin du texte s'il y en a un
        if (button->frame.text) {
                ei_point_t *where = malloc(sizeof(ei_point_t));
                int * width_txt = calloc(1, sizeof(int));
                int * height_txt = calloc(1, sizeof(int));
                hw_text_compute_size(button->frame.text, button->frame.text_font, width_txt, height_txt);
                where->x = widget->screen_location.top_left.x + widget->screen_location.size.width/2 - *width_txt/2;
                where->y = widget->screen_location.top_left.y + widget->screen_location.size.height/2 - *height_txt/2;

                ei_rect_t * clipper_button_text = widget->content_rect;
                if(clipper_button_text->top_left.x + clipper_button_text->size.width > clipper->top_left.x + clipper->size.width)
                        clipper_button_text->size.width = clipper->top_left.x + clipper->size.width  - clipper_button_text->top_left.x;
                if(clipper_button_text->top_left.y + clipper_button_text->size.height > clipper->top_left.y + clipper->size.height)
                        clipper_button_text->size.height = clipper->top_left.y + clipper->size.height  - clipper_button_text->top_left.y;

                ei_draw_text(surface, where, button->frame.text,
                             button->frame.text_font, button->frame.text_color, clipper_button_text);
                free(width_txt);
                free(height_txt);
                free(where);
        }
        hw_surface_unlock(surface);
        hw_surface_update_rects(surface, NULL);
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
void* button_allocfunc(){
        return calloc(1, sizeof(ei_button_t));
}

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
void button_releasefunc(ei_button_t* button){
        //free(button->frame.text);
        //free(button->frame.img_rect);
        free(button);
}

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to initialize.
 */
void button_setdefaultsfunc(ei_widget_t* widget){
        ei_button_t* button = (ei_button_t*)widget;
        frame_setdefaultsfunc(&(button->frame.widget));

        button->frame.relief = ei_relief_raised;
        button->frame.border_width = k_default_button_border_width;
        button->corner_radius = k_default_button_corner_radius;
        button->callback = NULL;
        button->user_param = NULL;

}

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
void button_geomnotifyfunc(ei_widget_t* widget){

}