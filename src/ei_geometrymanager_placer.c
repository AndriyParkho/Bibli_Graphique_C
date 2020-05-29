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

        // On détermine la taille du widget à partir des paramètres du placer et du parent
        ei_size_t widget_size;
        widget_size.width = clipper->size.width * placer->rel_width + placer->width;
        widget_size.height = clipper->size.height * placer->rel_height + placer->height;
        widget->screen_location.size = widget_size;

        // On détermine la position topleft du widget à partir des paramètre du placer, du parent et de l'ancre
        ei_point_t point_ancre;
        point_ancre.x = clipper->top_left.x + clipper->size.width * placer->rel_x + placer->x;
        point_ancre.y = clipper->top_left.y + clipper->size.height * placer->rel_y + placer->y;
        widget->screen_location.top_left = anchor_to_topleft(widget, placer->anchor, point_ancre);

        // On détermine s'il y a besoinde modifier le content_rect dans le cas où le widget dépasse de son parent
        ei_bool_t right_exceed = widget->content_rect->top_left.x + widget->content_rect->size.width > clipper->top_left.x + clipper->size.width;
        ei_bool_t bottom_exceed = widget->content_rect->top_left.y + widget->content_rect->size.height > clipper->top_left.y + clipper->size.height;
        ei_bool_t left_exceed = widget->content_rect->top_left.x < clipper->top_left.x;
        ei_bool_t top_exceed = widget->content_rect->top_left.y < clipper->top_left.y;

        if(right_exceed || bottom_exceed || left_exceed || top_exceed){
                ei_rect_t * new_content_rect = (ei_rect_t*)malloc(sizeof(ei_rect_t));
                new_content_rect->size.width = widget->content_rect->size.width;
                new_content_rect->size.height = widget->content_rect->size.height;
                new_content_rect->top_left = widget->content_rect->top_left;
                if(right_exceed){
                        new_content_rect->size.width = clipper->top_left.x + clipper->size.width  - new_content_rect->top_left.x;
                }
                else if(left_exceed){
                        new_content_rect->size.width = new_content_rect->top_left.x + new_content_rect->size.width  - clipper->top_left.x;
                        new_content_rect->top_left.x = clipper->top_left.x;
                }

                if(bottom_exceed)
                        new_content_rect->size.height = clipper->top_left.y + clipper->size.height  - new_content_rect->top_left.y;
                else if(top_exceed){
                        new_content_rect->size.height = new_content_rect->top_left.y + new_content_rect->size.height  - clipper->top_left.y;
                        new_content_rect->top_left.y = clipper->top_left.y;
                }
                widget->content_rect = new_content_rect;
        }

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


/**
 * \brief	Fonction qui permet de calculer le point top_left d'un rectangle selon l'ancre du widget
 *
 * @param	widget		Le widget dont il faut déterminier le point top_left
 * @param       anchor          L'ancre du widget (par défaut ei_anc_northwest)
 * @param       point           Le point dont il faut modifier les coordonées pour obtenir le point top_left
 */
ei_point_t anchor_to_topleft(ei_widget_t * widget, ei_anchor_t anchor, ei_point_t point){
        ei_point_t new_top_left;
        if (anchor == ei_anc_none || anchor == ei_anc_northwest)
                return point;
        else if (anchor == ei_anc_center){
                new_top_left.x = point.x - widget->screen_location.size.width/2;
                new_top_left.y = point.y - widget->screen_location.size.height/2;
                return new_top_left;
        } else if (anchor == ei_anc_north){
                new_top_left.x = point.x - widget->screen_location.size.width/2;
                new_top_left.y = point.y;
                return new_top_left;
        } else if (anchor == ei_anc_northeast){
                new_top_left.x = point.x - widget->screen_location.size.width;
                new_top_left.y = point.y;
                return new_top_left;
        } else if (anchor == ei_anc_east){
                new_top_left.x = point.x - widget->screen_location.size.width;
                new_top_left.y = point.y - widget->screen_location.size.width/2;
                return new_top_left;
        } else if (anchor == ei_anc_southeast){
                new_top_left.x = point.x - widget->screen_location.size.width;
                new_top_left.y = point.y - widget->screen_location.size.width;
                return new_top_left;
        } else if (anchor == ei_anc_south){
                new_top_left.x = point.x - widget->screen_location.size.width/2;
                new_top_left.y = point.y - widget->screen_location.size.width;
                return new_top_left;
        } else if (anchor == ei_anc_southwest){
                new_top_left.x = point.x;
                new_top_left.y = point.y - widget->screen_location.size.width;
                return new_top_left;
        } else if (anchor == ei_anc_west){
                new_top_left.x = point.x;
                new_top_left.y = point.y - widget->screen_location.size.width/2;
                return new_top_left;
        } else{
                return point;
        }
}