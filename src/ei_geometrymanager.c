//
// Created by andriy on 12/05/2020.
//

#include "ei_geometrymanager.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_geometrymanager_parcours.h"
#include "ei_geometrymanager_placer.h"
#include <string.h>
#include "ei_geometrytypes.h"
#include <stdlib.h>

struct ei_geometrymanager_t;
struct ei_geometry_param_t;


/**
 * \brief	A name of a geometry manager.
 */
typedef char	ei_geometrymanager_name_t[20];

/**
 * \brief	A function that runs the geometry computation for this widget. This may trigger
 *		geometry computation for this widget's parent and the other children of the parent.
 *
 * @param	widget		The widget instance for which to compute geometry.
 */
typedef void	(*ei_geometrymanager_runfunc_t)		(struct ei_widget_t*	widget);

/**
 * \brief	A function called when a widget cease to be managed by its geometry manager.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets.
 *
 * @param	widget		The widget instance that must be forgotten by the geometry manager.
 */
typedef void	(*ei_geometrymanager_releasefunc_t)	(struct ei_widget_t*	widget);



/**
 * \brief	Registers a geometry manager to the program so that it can be called to manager
 *		widgets. This must be done only once in the application.
 *
 * @param	geometrymanager		The structure describing the geometry manager.
 */
void			ei_geometrymanager_register	(ei_geometrymanager_t* geometrymanager){
        inserer_geometrymanager_queue(&geometrymanager_tete, geometrymanager);
}



/**
 * \brief	Returns a geometry manager structure from its name.
 *
 * @param	name		The name of the geometry manager.
 *
 * @return			The structure describing the geometry manager.
 */
ei_geometrymanager_t*	ei_geometrymanager_from_name	(ei_geometrymanager_name_t name){
        return trouve_geomanager(&geometrymanager_tete, name);
}



/**
 * \brief	Tell the geometry manager in charge of a widget to forget it. This removes the
 *		widget from the screen. If the widget is not currently managed, this function
 *		returns silently.
 *		Side effects:
 *		<ul>
 *			<li> the \ref ei_geometrymanager_releasefunc_t of the geometry manager in
 *				charge of this widget is called, </li>
 *			<li> the geom_param field of the widget is freed, </li>
 *			<li> the current screen_location of the widget is invalided (which will
 *				trigger a redraw), </li>
 *			<li> the screen_location of the widget is reset to 0. </li>
 *		</ul>
 *
 * @param	widget		The widget to unmap from the screen.
 */
void			ei_geometrymanager_unmap	(ei_widget_t*		widget){

}



/**
 * \brief	Registers the "placer" geometry manager in the program. This must be called only
 *		once before the \ref ei_place function can be called.
 */
void 			ei_register_placer_manager 	(void){
        ei_geometrymanager_t *placer = malloc(sizeof(ei_geometrymanager_t));
        strcpy(placer->name, "placer");
        placer->runfunc = &placer_runfunc;
        placer->releasefunc = &placer_releasefunc;
        placer->next = NULL;
        ei_geometrymanager_register(placer);
}



/**
 * \brief	Configures the geometry of a widget using the "placer" geometry manager.
 * 		If the widget was already managed by another geometry manager, then it is first
 *		removed from the previous geometry manager.
 * 		If the widget was already managed by the "placer", then this calls simply updates
 *		the placer parameters: arguments that are not NULL replace previous values.
 * 		When the arguments are passed as NULL, the placer uses default values (detailed in
 *		the argument descriptions below). If no size is provided (either absolute or
 *		relative), then the requested size of the widget is used, i.e. the minimal size
 *		required to display its content.
 *
 * @param	widget		The widget to place.
 * @param	anchor		How to anchor the widget to the position defined by the placer
 *				(defaults to ei_anc_northwest).
 * @param	x		The absolute x position of the widget (defaults to 0) in the
 *				parent's reference.
 * @param	y		The absolute y position of the widget (defaults to 0) in the
 *				parent's reference.
 * @param	width		The absolute width for the widget (defaults to the requested width
 *				of the widget if rel_width is NULL, or 0 otherwise).
 * @param	height		The absolute height for the widget (defaults to the requested height
 *				of the widget if rel_height is NULL, or 0 otherwise).
 * @param	rel_x		The relative x position of the widget: 0.0 corresponds to the left
 *				side of the parent, 1.0 to the right side (defaults to 0.0).
 * @param	rel_y		The relative y position of the widget: 0.0 corresponds to the top
 *				side of the parent, 1.0 to the bottom side (defaults to 0.0).
 * @param	rel_width	The relative width of the widget: 0.0 corresponds to a width of 0,
 *				1.0 to the width of the parent (defaults to 0.0).
 * @param	rel_height	The relative height of the widget: 0.0 corresponds to a height of 0,
 *				1.0 to the height of the parent (defaults to 0.0).
 */
void			ei_place			(ei_widget_t*		widget,
                                                             ei_anchor_t*		anchor,
                                                             int*			x,
                                                             int*			y,
                                                             int*			width,
                                                             int*			height,
                                                             float*			rel_x,
                                                             float*			rel_y,
                                                             float*			rel_width,
                                                             float*			rel_height){
    ei_geometrymanager_t* geometrymanager = trouve_geomanager(&geometrymanager_tete, "placer");
    ei_placer_param_t* placer;
    if (widget->geom_params->manager) {
        if (strcmp(widget->geom_params->manager->name, "placer") != 0) {
            widget->geom_params->manager->releasefunc(widget);
            placer->geomanager = geometrymanager;
            widget->geom_params = (ei_geometry_param_t *)placer;
        }
        else
            placer = (ei_placer_param_t *)widget->geom_params;
    }
    else {
        placer->geomanager = geometrymanager;
        widget->geom_params = (ei_geometry_param_t *)placer;
    }

    if (anchor) placer->anchor = *anchor;
    else placer->anchor = ei_anc_northwest;

    if (x) placer->x = *x;
    else placer->x = 0;

    if (y) placer->y = *y;
    else placer->y = 0;

    if (width) placer->width = *width;
    else if (rel_width) {
        placer->width = 0;
        placer->rel_width = *rel_width;
    }
    else {
        placer->width = widget->requested_size.width;
        placer->rel_width = (float)0.0;
    }

    if (height) placer->height = *height;
    else if (rel_height) {
        placer->height = 0;
        placer->rel_height = *rel_height;
    }
    else {
        placer->height = widget->requested_size.height;
        placer->rel_height = (float)0.0;
    }

    if (rel_x) placer->rel_x = *rel_x;
    else placer->rel_x = (float)0.0;

    if (rel_y) placer->rel_y = *rel_y;
    else placer->rel_y = (float)0.0;
}

