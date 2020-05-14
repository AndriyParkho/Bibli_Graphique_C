/*
 *  Fichier où il y aura toutes les fonctions des différents widgets
 */
#include "ei_draw.h"
#include "ei_widgettypes.h"

void frame_drawfunc(ei_widget_t* widget, ei_surface_t draw_surface, ei_surface_t pick_surface, ei_rect_t* clipper){
        ei_draw_polygon(draw_surface, first_point, widget.pick_color, NULL);
}


void ei_frame_allocfunc(){
        return(calloc(sizeof(ei_frame_t)));
}


void ei_frame_releasefunc(ei_frame_t* frame){
        free(frame);
}


void ei_frame_setdefaultsfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}


void ei_frame_geomnotifyfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}