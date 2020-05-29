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
void ei_toplevel_setdefaultsfunc(ei_toplevel_t* toplevel) {
        ei_size_t default_size = {320,240};
        ei_size_t min_default_size = {160, 120};
        frame_setdefaultsfunc(&toplevel->frame);
        toplevel->frame.widget.requested_size = default_size;
        toplevel->frame.border_width = 4;

        // On créer la title bar
        ei_button_t * title_bar = ei_widget_create("button", NULL, NULL, NULL);
        // On initialise les paramètres du bouton de fermeture
        ei_size_t       title_bar_size          = {default_size.width, 30};
        ei_color_t      title_bar_color         = {0x69, 0x69, 0x76, 0xff};
        char*           title_bar_text          = "TopLevel";
        ei_color_t      title_color             = {0x00, 0x00, 0x00, 0xff};
        ei_anchor_t     title_anc               = ei_anc_northwest;
        int             title_bar_border        = 0;
        int             title_bar_radius        = 15;
        ei_relief_t     title_bar_relief        = ei_relief_none;
        ei_button_configure(title_bar, &title_bar_size, &title_bar_color, &title_bar_border, &title_bar_radius, &title_bar_relief,
                                &title_bar_text, NULL, &title_color, &title_anc, NULL, NULL, NULL, NULL, NULL);
        toplevel->title_bar = title_bar;


        toplevel->closable = EI_TRUE;
        // On créer le bouton de fermeture
        ei_button_t * close_button = ei_widget_create("button", title_bar, NULL, NULL);
        // On initialise les paramètres du bouton de fermeture
        ei_color_t      close_color             = {0xff, 0x00, 0x00, 0xff};
        char*           text_close              = "X";
        ei_color_t      close_text_color        = {0x00, 0x00, 0x00, 0xff};
        ei_anchor_t     text_close_anc          = ei_anc_northwest;
        int             close_border_width      = 0;
        int             close_button_radius     = 10;
        ei_relief_t     close_button_relief     = ei_relief_none;
        ei_button_configure(close_button, NULL, &close_color, &close_border_width, &close_button_radius, &close_button_relief,
                                &text_close, NULL, &close_text_color, &text_close_anc, NULL, NULL, NULL, NULL, NULL);
        // On change la taille ici car dépend du rayon
        close_button->frame.widget.requested_size = ei_size(toplevel->close_button->corner_radius * 2, toplevel->close_button->corner_radius * 2);
        toplevel->close_button = close_button;

        toplevel->window_resizable = ei_axis_both;
        // On créer le bouton de redimensionnement
        ei_button_t * resize_button = ei_widget_create("button", NULL, NULL, NULL);
        // On initialise les paramètres du bouton de redimensionnement
        ei_size_t       resize_button_size      = {5, 5};
        ei_color_t      resize_button_color     = title_bar_color;
        int             resize_button_border    = 0;
        int             resize_button_radius    = 0;
        ei_relief_t     resize_button_relief    = ei_relief_none;
        ei_button_configure(resize_button, &resize_button_size, &resize_button_color, &resize_button_border, &resize_button_radius,
                                &resize_button_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        toplevel->resize_button = resize_button;

        toplevel->min_size = &min_default_size;
}

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
void ei_toplevel_geomnotifyfunc(ei_widget_t* widget);

