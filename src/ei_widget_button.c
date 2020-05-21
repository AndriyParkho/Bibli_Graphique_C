/*
 * Fonctions propres au widget button
 */

#include "ei_widget_button.h"


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

void button_drawfunc(ei_widget_t *widget){
        ei_frame_t* button = (ei_button_t*)widget;
        rounded_frame(button->widget.screen_location); // Partie haute
        rounded_frame(button->widget.screen_location); // Partie basse
        rounded_frame(button->widget.screen_location); // Partie supérieure
}

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

void button_setdefaultsfunc(ei_widget_t* widget){
        ei_button_t* button = (ei_button_t*)widget;
        button->frame.widget.wclass->setdefaultsfunc((ei_widget_t)button->frame);

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