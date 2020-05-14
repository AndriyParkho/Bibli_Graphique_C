/*
 *  Fichier où il y aura toutes les fonctions des différents widgets
 */
#include "../include/ei_draw.h"
#include <stdlib.h>
#include "../ei_widget.h"

void frame_drawfunc(ei_widget_t* widget, ei_surface_t draw_surface, ei_surface_t pick_surface, ei_rect_t* clipper){
        ei_fill(draw_surface, widget.pick_color, clipper);
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