//
// Created by andriy on 13/05/2020.
//


#include "hw_interface.h"
#include "ei_draw.h"
#include <string.h>
#include <ei_widget_frame.h>
#include <ei_widgetclass_parcours.h>
#include <stdlib.h>
#include "ei_widget_button.h"


/**
 * \brief	A name of a class of widget.
 */
typedef char 		ei_widgetclass_name_t[20];

struct ei_widget_t;
struct ei_widgetclass_t;

/**
 * \brief	A function that allocates a block of memory that is big enough to store the
 *		attributes of a widget of a class. After allocation, the function *must*
 *		initialize the memory to 0.
 *
 * @return		A block of memory with all bytes set to 0.
 */
typedef void*	(*ei_widgetclass_allocfunc_t)		(void);

/**
 * \brief	A function that releases the memory used by a widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
typedef void	(*ei_widgetclass_releasefunc_t)		(struct ei_widget_t*	widget);

/**
 * \brief	A function that draws widgets of a class.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	pick_surface	The surface used for picking (i.e. find the widget below the mouse pointer).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
typedef void	(*ei_widgetclass_drawfunc_t)		(struct ei_widget_t*	widget,
                                                                 ei_surface_t		surface,
                                                                 ei_surface_t		pick_surface,
                                                                 ei_rect_t*		clipper);

/**
 * \brief	A function that sets the default values for a class.
 *
 * @param	widget		A pointer to the widget instance to initialize.
 */
typedef void	(*ei_widgetclass_setdefaultsfunc_t)	(struct ei_widget_t*	widget);

/**
 * \brief 	A function that is called to notify the widget that its geometry has been modified
 *		by its geometry manager. Can set to NULL in \ref ei_widgetclass_t.
 *
 * @param	widget		The widget instance to notify of a geometry change.
 */
typedef void	(*ei_widgetclass_geomnotifyfunc_t)	(struct ei_widget_t*	widget);


/**
 * \brief	Returns the string of the name of a class.
 *
 * @param	name		The class name.
 *
 * @return			The string representing the name of the class.
 */
static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name){
    return (char*)name;
}

/**
 * @brief	Registers a class to the program so that widgets of this class can be created.
 *		This must be done only once per widget class in the application.
 *
 * @param	widgetclass	The structure describing the class.
 */
void			ei_widgetclass_register		(ei_widgetclass_t* widgetclass){
        insere_class_queue(&class_tete, widgetclass);
}


/**
 * @brief	Returns the structure describing a class, from its name.
 *
 * @param	name		The name of the class of widget.
 *
 * @return			The structure describing the class.
 */
ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name){
        return trouve_class(&class_tete, name);
}

/**
 * \brief	Registers the "frame" widget class in the program. This must be called only
 *		once before widgets of the class "frame" can be created and configured with
 *		\ref ei_frame_configure.
 */
void			ei_frame_register_class 	(void){
        ei_widgetclass_t *frame = malloc(sizeof(ei_widgetclass_t));
        strcpy(frame->name, "frame");
        frame->allocfunc = &frame_allocfunc;
        frame->releasefunc = (ei_widgetclass_releasefunc_t) &frame_releasefunc;
        frame->drawfunc = (ei_widgetclass_drawfunc_t) &frame_drawfunc;
        frame->setdefaultsfunc = &frame_setdefaultsfunc;
        frame->geomnotifyfunc = NULL; // En attendant de comprendre à quoi sert &frame_geomnotifyfunc;
        frame->next = NULL;
        ei_widgetclass_register(frame);
}

/**
 * \brief	Registers the "button" widget class in the program. This must be called only
 *		once before widgets of the class "button" can be created and configured with
 *		\ref ei_button_configure.
 */
void			ei_button_register_class 	(){
        ei_widgetclass_t *button = malloc(sizeof(ei_widgetclass_t*));
        strcpy(button->name, "button");
        button->allocfunc = &button_allocfunc;
        button->releasefunc = (ei_widgetclass_releasefunc_t) &button_releasefunc;
        button->drawfunc = (ei_widgetclass_drawfunc_t) &button_drawfunc;
        button->setdefaultsfunc = &button_setdefaultsfunc;
        button->geomnotifyfunc = NULL; // En attendant de comprendre à quoi sert &button_geomnotifyfunc;
        button->next = NULL;
        ei_widgetclass_register(button);
}

/**
 * \brief	Registers the "toplevel" widget class in the program. This must be called only
 *		once before widgets of the class "toplevel" can be created and configured with
 *		\ref ei_toplevel_configure.
 */
void			ei_toplevel_register_class 	(void){
        
}


/* Inline function definitions. */
/*
static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name)
{
        return (char*)name;
}
*/