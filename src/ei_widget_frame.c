/*
 *  Fichier où il y aura toutes les fonctions des différents widgets
 */
#include "ei_draw.h"

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
void frame_draw(ei_widget_t* widget){
        ei_draw_polygon(main_window, points, transp_blue, NULL);
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