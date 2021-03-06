/*
Fonction pour implémenter les widget
*/

#include "ei_draw.h"
#include "ei_widgetclass.h"
#include "ei_widgettypes.h"
#include <string.h>
#include "ei_widgetclass_parcours.h"
#include <stdlib.h>
#include <assert.h>
#include "ei_application.h"
#include "ei_draw_annexe.h"
#include "ei_utils.h"

struct ei_geometry_param_t;
struct ei_event_t;
struct ei_widget_t;

static uint32_t count_pick_id = 1;
static ei_color_t count_pick_color = {0x00, 0x00, 0x01, 0xff};

/**
 * @brief	The type of functions that are called in response to a user event. Usually passed as a
 *		parameter to \ref ei_bind.
 *
 * @param	widget		The widget for which the event was generated.
 * @param	event		The event containing all its parameters (type, etc.)
 * @param	user_param	The user parameters that was provided by the caller when registering
 *				this callback.
 *
 * @return			A boolean telling if the event was consumed by the callback or not.
 *				If TRUE, the library does not try to call other callbacks for this
 *				event. If FALSE, the library will call the next callback registered
 *				for this event, if any.
 *				Note: The callback may execute many operations and still return
 *				FALSE, or return TRUE without having done anything.
 */
typedef ei_bool_t	(*ei_callback_t)	(struct ei_widget_t*	widget,
                                                  struct ei_event_t*	event,
                                                  void*			user_param);

/**
 * @brief	The type of functions that are called just before a widget is being destroyed (i.e. the
 * 		passed widget structure and its fields are still valid). Passed as a parameter to
 * 		\ref ei_widget_create.
 *
 * @param	widget		The widget that is going to be destroyed.
 */
typedef void		(*ei_widget_destructor_t)(struct ei_widget_t* widget);



/**
 * @brief	Creates a new instance of a widget of some particular class, as a descendant of
 *		an existing widget.
 *
 *		The widget is not displayed on screen until it is managed by a geometry manager.
 *		The widget should be released by calling \ref ei_widget_destroy when no more needed.
 *
 * @param	class_name	The name of the class of the widget that is to be created.
 * @param	parent 		A pointer to the parent widget. Can not be NULL.
 * @param	user_data	A pointer provided by the programmer for private use. May be NULL.
 * @param	destructor	A pointer to a function to call before destroying a widget structure. May be NULL.
 *
 * @return			The newly created widget, or NULL if there was an error.
 */
ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                                                             struct ei_widget_t*		parent,
                                                             void*			user_data,
                                                             ei_widget_destructor_t destructor){
        ei_widgetclass_t *widgetclass =  ei_widgetclass_from_name(class_name);
        ei_widget_t *new_widget = (ei_widget_t*)widgetclass->allocfunc();
        new_widget->wclass = widgetclass;
        new_widget->wclass->setdefaultsfunc(new_widget);
        new_widget->pick_id = count_pick_id;
        count_pick_id++;
        ei_color_t* pick_color = malloc(sizeof(ei_color_t));
        *pick_color = count_pick_color;
        if (count_pick_color.blue == 0xff) {
                count_pick_color.blue = 0x00;
                if (count_pick_color.green == 0xff) {
                        count_pick_color.green = 0x00;
                        if (count_pick_color.red == 0xff) {
                                count_pick_color.red = 0x00;
                        }
                        else count_pick_color.red++;
                }
                else count_pick_color.green++;
        }
        else count_pick_color.blue++;
        new_widget->pick_color = pick_color;
        new_widget->user_data = user_data;
        new_widget->destructor = destructor;

        /* Widget Hierachy Management */
        new_widget->parent = parent;
        add_widget_child(parent, new_widget);
        new_widget->children_head = NULL;
        new_widget->children_tail = NULL;
        new_widget->next_sibling = NULL;

        /* Geometry Management */
        new_widget->geom_params = NULL;
        if (parent) new_widget->requested_size = parent->requested_size;            // Je sais pas
        if (parent) new_widget->screen_location = *(parent->content_rect);          // si ces champs sont
        new_widget->content_rect = &(new_widget->screen_location);      //  bien initialisés
        return new_widget;
}

/**
 * @brief	Destroys a widget. Calls destructor if any. Removes the widget from screen if it is
 * 		currently managed by a geometry manager. Destroys all its descendants.
 *
 * @param	widget		The widget that is to be destroyed.
 */
void			ei_widget_destroy		( ei_widget_t*		widget){
        if (widget->parent->children_head==widget) {
                widget->parent->children_head = widget->next_sibling;
                if (widget->parent->children_tail == widget) widget->parent->children_tail = NULL;
        }
        else {
                ei_widget_t* wcour = widget->parent->children_head->next_sibling;
                ei_widget_t* wpred = widget->parent->children_head;
                while (wcour->pick_id != widget->pick_id) {
                        wpred = wcour;
                        wcour = wcour->next_sibling;
                }
                wpred->next_sibling = wcour->next_sibling;
                if (wcour == widget->parent->children_tail) widget->parent->children_tail = wpred;
        }
        widget->wclass->releasefunc(widget);
}


/**
 * @brief	Returns the widget that is at a given location on screen.
 *
 * @param	where		The location on screen, expressed in the root window coordinates.
 *
 * @return			The top-most widget at this location, or NULL if there is no widget
 *				at this location (except for the root widget).
 */
ei_widget_t*		ei_widget_pick			(ei_point_t*		where){
        uint32_t* pixel_ptr = hw_surface_get_buffer(get_root_offscreen());
        ei_size_t surface_size = hw_surface_get_size(get_root_offscreen());
        pixel_ptr = pixel_ptr + surface_size.width * where->y + where->x;
        ei_widget_t* widget = ei_widget_pick_rec(ei_app_root_widget(), *pixel_ptr);
        return widget;
}




/**
 * @brief	Configures the attributes of widgets of the class "frame".
 *
 *		Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
 *		been defined before, then a default value should be used (default values are
 *		specified for each parameter). If the parameter is "NULL" but was defined on a
 *		previous call, then its value must not be changed.
 *
 * @param	widget		The widget to configure.
 * @param	requested_size	The size requested for this widget, including borders.
 *				The geometry manager may override this size due to other constraints.
 *				Defaults to the "natural size" of the widget, ie. big enough to
 *				display the border and the text or the image. This may be (0, 0)
 *				if the widget has border_width=0, and no text and no image.
 * @param	color		The color of the background of the widget. Defaults to
 *				\ref ei_default_background_color.
 * @param	border_width	The width in pixel of the border decoration of the widget. The final
 *				appearance depends on the "relief" parameter. Defaults to 0.
 * @param	relief		Appearance of the border of the widget. Defaults to
 *				\ref ei_relief_none.
 * @param	text		The text to display in the widget, or NULL. Only one of the
 *				parameter "text" and "img" should be used (i.e. non-NULL). Defaults
 *				to NULL.
 * @param	text_font	The font used to display the text. Defaults to \ref ei_default_font.
 * @param	text_color	The color used to display the text. Defaults to
 *				\ref ei_font_default_color.
 * @param	text_anchor	The anchor of the text, i.e. where it is placed whithin the widget.
 *				Defines both the anchoring point on the parent and on the widget.
 *				Defaults to \ref ei_anc_center.
 * @param	img		The image to display in the widget, or NULL. Any surface can be
 *				used, but usually a surface returned by \ref hw_image_load. Only one
 *				of the parameter "text" and "img" should be used (i.e. non-NULL).
 				Defaults to NULL.
 * @param	img_rect	If not NULL, this rectangle defines a subpart of "img" to use as the
 *				image displayed in the widget. Defaults to NULL.
 * @param	img_anchor	The anchor of the image, i.e. where it is placed within the widget
 *				when the size of the widget is bigger than the size of the image.
 *				Defaults to \ref ei_anc_center.
 */
void			ei_frame_configure		(ei_widget_t*		widget,
                                                               ei_size_t*		requested_size,
                                                               const ei_color_t*	color,
                                                               int*			border_width,
                                                               ei_relief_t*		relief,
                                                               char**			text,
                                                               ei_font_t*		text_font,
                                                               ei_color_t*		text_color,
                                                               ei_anchor_t*		text_anchor,
                                                               ei_surface_t*		img,
                                                               ei_rect_t**		img_rect,
                                                               ei_anchor_t*		img_anchor){
        assert(!(text != NULL && img!=NULL));
        ei_frame_t* frame = (ei_frame_t*)widget;

        if (requested_size) frame->widget.requested_size = *requested_size;

        //ei_rect_t screen_location = {(0,0),requested_size};
        //frame->widget.screen_location = screen_location;
        if (color) frame->color = *color;
        if (border_width) frame->border_width = *border_width;
        if (relief) frame->relief = *relief;
        if (text) frame->text = *text;
        if (text_font) frame->text_font = *text_font;
        if (text_color) frame->text_color = *text_color;
        if (text_anchor) frame->text_anchor = *text_anchor;
        if (img) frame->img = *img;
        if (img_rect) frame->img_rect = *img_rect;
        if (img_anchor) frame->img_anchor = *img_anchor;

        if (img && !requested_size) frame->widget.requested_size = (*img_rect)->size;
        if (text && !requested_size) hw_text_compute_size(*text, frame->text_font, &frame->widget.requested_size.width, &frame->widget.requested_size.height);
}

/**
 * @brief	Configures the attributes of widgets of the class "button".
 *
 * @param	widget, requested_size, color, border_width, relief,
 *		text, text_font, text_color, text_anchor,
 *		img, img_rect, img_anchor
 *				See the parameter definition of \ref ei_frame_configure. The only
 *				difference is that relief defaults to \ref ei_relief_raised
 *				and border_width defaults to \ref k_default_button_border_width.
 * @param	corner_radius	The radius (in pixels) of the rounded corners of the button.
 *				0 means straight corners. Defaults to \ref k_default_button_corner_radius.
 * @param	callback	The callback function to call when the user clicks on the button.
 *				Defaults to NULL (no callback).
 * @param	user_param	A programmer supplied parameter that will be passed to the callback
 *				when called. Defaults to NULL.
 */
void			ei_button_configure		(ei_widget_t*		widget,
                                                                ei_size_t*		requested_size,
                                                                const ei_color_t*	color,
                                                                int*			border_width,
                                                                int*			corner_radius,
                                                                ei_relief_t*		relief,
                                                                char**			text,
                                                                ei_font_t*		text_font,
                                                                ei_color_t*		text_color,
                                                                ei_anchor_t*		text_anchor,
                                                                ei_surface_t*		img,
                                                                ei_rect_t**		img_rect,
                                                                ei_anchor_t*		img_anchor,
                                                                ei_callback_t*		callback,
                                                                void**			user_param){
        ei_button_t* button = (ei_button_t*)widget;
        if (corner_radius) button->corner_radius = *corner_radius;
        ei_frame_configure((ei_widget_t *)&button->frame,requested_size,color,border_width,relief,text,text_font,text_color,
                           text_anchor, img, img_rect, img_anchor);
        if (callback) button->callback = *callback;
        if (user_param) button->user_param = *user_param;
        if (callback) {
                ei_bind(ei_ev_mouse_buttondown, button, NULL, button->callback, button->user_param);
        }
}

/**
 * @brief	Configures the attributes of widgets of the class "toplevel".
 *
 * @param	widget		The widget to configure.
 * @param	requested_size	The content size requested for this widget, this does not include
 *				the decorations	(border, title bar). The geometry manager may
 *				override this size due to other constraints.
 *				Defaults to (320x240).
 * @param	color		The color of the background of the content of the widget. Defaults
 *				to \ref ei_default_background_color.
 * @param	border_width	The width in pixel of the border of the widget. Defaults to 4.
 * @param	title		The string title displayed in the title bar. Defaults to "Toplevel".
 *				Uses the font \ref ei_default_font.
 * @param	closable	If true, the toplevel is closable by the user, the toplevel must
 *				show a close button in its title bar. Defaults to \ref EI_TRUE.
 * @param	resizable	Defines if the widget can be resized horizontally and/or vertically
 *				by the user. Defaults to \ref ei_axis_both.
 * @param	min_size	For resizable widgets, defines the minimum size of its content.
 *				The default minimum size of a toplevel is (160, 120).
 *				If *min_size is NULL, this requires the toplevel to be configured to
 *				its default size.
 */
void			ei_toplevel_configure		( ei_widget_t*		widget,
                                                                  ei_size_t*		requested_size,
                                                                  ei_color_t*		color,
                                                                  int*			border_width,
                                                                  char**		title,
                                                                  ei_bool_t*		closable,
                                                                  ei_axis_set_t*	resizable,
                                                                  ei_size_t**		min_size){
        ei_toplevel_t * toplevel = (ei_toplevel_t *)widget;

        if(requested_size) toplevel->frame.widget.requested_size = *requested_size;

        if(color) toplevel->frame.color = *color;
        if(border_width) toplevel->frame.border_width = *border_width;
        if(title) toplevel->frame.text = *title;

        if(closable) toplevel->closable = *closable;
        if(resizable) toplevel->window_resizable = *resizable;
        if(min_size) toplevel->min_size = *min_size;
}


