/**
 *  @file	ei_widget_toplevel.h
 *  @brief	Gère les différentes fonctions qui sont liées aux widgets de type toplevel
 *
 *  \author Created by Equipe 5 on 28.05.2020.
 */

#include "ei_widget_toplevel.h"

/**
 * \brief	A function that draws toplevel.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	pick_surface	The surface used for picking (i.e. find the widget below the mouse pointer).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference toplevel).
 */
void toplevel_drawfunc(ei_widget_t        *widget,
                    ei_surface_t	surface,
                    ei_surface_t	pick_surface,
                    ei_rect_t*		clipper);

/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
void* ei_toplevel_allocfunc() {
        return (void*) calloc(1, sizeof(ei_toplevel_t));
}

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
void ei_toplevel_releasefunc(ei_toplevel_t* toplevel) {
        free(toplevel);
}

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to initialize.
 */
 /*
void ei_toplevel_setdefaultsfunc(ei_toplevel_t* toplevel) {
        ei_size_t default_size = {320,240};
        ei_size_t min_default_size = {160, 120};
        frame_setdefaultsfunc(&toplevel->frame);
        toplevel->frame.widget.requested_size = default_size;
        toplevel->frame.border_width = 4;

        button_setdefaultsfunc(toplevel->title_bar);
        strcpy(toplevel->title_bar->frame.text, "TopLevel");

        toplevel->closable = EI_TRUE;
        frame_setdefaultsfunc(&(toplevel->close_button->frame.widget));
        toplevel->close_button->frame.relief = ei_relief_none;
        toplevel->close_button->frame.border_width = 0;
        toplevel->close_button->corner_radius = 10;
        toplevel->close_button->frame.widget.requested_size = ei_size(toplevel->close_button->corner_radius * 2, toplevel->close_button->corner_radius * 2);
        toplevel->close_button->frame.text = "X";
        toplevel->close_button->frame.text_color = ei_color_t(0x00, 0x00, 0x00, 0xff);

        toplevel->window_resizable = ei_axis_both;

        toplevel->min_size = &min_default_size;
}
*/
/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
void ei_toplevel_geomnotifyfunc(ei_widget_t* widget);

