/*
 *  Fichier où il y aura toutes les fonctions des différents widgets
 */
#include "ei_widget_frame.h"

void frame_drawfunc(ei_widget_t* widget, ei_surface_t draw_surface, ei_surface_t pick_surface, ei_rect_t* clipper){
        ei_fill(draw_surface, NULL, NULL);
}

void* frame_allocfunc(){
        return(calloc(1, sizeof(ei_frame_t)));
}

void frame_releasefunc(ei_frame_t* frame){
        free(frame);
}

void frame_setdefaultsfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}

void frame_geomnotifyfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}