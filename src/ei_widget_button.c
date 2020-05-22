/*
 * Fonctions propres au widget button
 */

#include "ei_widget_button.h"
#include "ei_application.h"


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
/*
void button_drawfunc(ei_widget_t *widget){
        ei_button_t* button = (ei_button_t*)widget;
        ei_linked_point_t* points;
        ei_color_t dark_color = {button->frame.color.red - 30, button->frame.color.green - 30,
                                 button->frame.color.blue - 30, button->frame.color.alpha};
        ei_color_t light_color = {button->frame.color.red + 30, button->frame.color.green + 30,
                                  button->frame.color.blue + 30, button->frame.color.alpha};
        ei_rect_t new_rect;

        hw_surface_lock(ei_app_root_surface());
        //Partie haute
        points = rounded_frame(button->frame.widget.screen_location, button->corner_radius,2);
        ei_draw_polygon(ei_app_root_surface(), points, light_color, &(widget->screen_location));

        //Partie basse
        points = rounded_frame(button->frame.widget.screen_location, button->corner_radius,1);
        ei_draw_polygon(ei_app_root_surface(), points, dark_color, &(widget->screen_location));

        //Totalité
        new_rect = widget->screen_location;
        new_rect.top_left.x += button->frame.border_width;
        new_rect.top_left.y += button->frame.border_width;
        new_rect.size.width -= 2*button->frame.border_width;
        new_rect.size.height -= 2*button->frame.border_width;
        points = rounded_frame(new_rect, button->corner_radius,0);
        ei_draw_polygon(ei_app_root_surface(), points, button->frame.color, &new_rect);
}
*/
/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
void* button_allocfunc(){
        return(calloc(1, sizeof(ei_button_t)));
}

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
void button_releasefunc(ei_widget_t* button){
        free(button);
}

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to initialize.
 */
/*
void button_setdefaultsfunc(ei_widget_t* widget){
        ei_button_t* button = (ei_button_t*)widget;
        button->frame.widget.wclass->setdefaultsfunc(&(button->frame.widget));

        button->frame.relief = ei_relief_raised;
        button->frame.border_width = k_default_button_border_width;
        button->corner_radius = k_default_button_corner_radius;
        button->callback = NULL;
        button->user_param = NULL;

}
 */

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
void button_geomnotifyfunc(ei_widget_t* widget){

}