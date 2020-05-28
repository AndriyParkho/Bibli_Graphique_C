/*
 * Fonctions propre au manager placer
 */


#include "ei_geometrymanager_placer.h"


/**
 * \brief	A function that runs the geometry computation for this widget. This may trigger
 *		geometry computation for this widget's parent and the other children of the parent, pour un
 *		geometrymanager de type placer
 *
 * @param	widget		The widget instance for which to compute geometry.
 */
void placer_runfunc(ei_widget_t* widget){
        ei_placer_param_t *placer = (ei_placer_param_t*) widget->geom_params;
        ei_widget_t* parent = widget->parent;
        ei_rect_t * clipper = parent->content_rect;

        ei_rect_t * clipper_button_text = (ei_rect_t*)malloc(sizeof(ei_rect_t));
        clipper_button_text->size.width = widget->content_rect->size.width;
        clipper_button_text->size.height = widget->content_rect->size.height;
        clipper_button_text->top_left = widget->content_rect->top_left;

        if(clipper_button_text->top_left.x + clipper_button_text->size.width > clipper->top_left.x + clipper->size.width)
                clipper_button_text->size.width = clipper->top_left.x + clipper->size.width  - clipper_button_text->top_left.x;
        if(clipper_button_text->top_left.y + clipper_button_text->size.height > clipper->top_left.y + clipper->size.height)
                clipper_button_text->size.height = clipper->top_left.y + clipper->size.height  - clipper_button_text->top_left.y;

        ei_rect_t screen_location;
        screen_location.size = widget->requested_size;
        screen_location.top_left.x = placer->x;
        screen_location.top_left.y = placer->y;
        widget->screen_location = screen_location;
}

/**
 * \brief	A function called when a widget cease to be managed by its geometry manager.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets, pour un geometrymanager de type placer
 *
 * @param	widget		The widget instance that must be forgotten by the geometry manager.
 */
void placer_releasefunc(ei_widget_t* widget){

}