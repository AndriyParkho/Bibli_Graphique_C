/**
 * Fonctions servant à dessiner les widgets et leurs détails
 */


#ifndef EI_DRAW_ANNEXE_H
#define EI_DRAW_ANNEXE_H

#include "ei_draw.h"

ei_linked_point_t * arc(ei_point_t centre, int rayon, double angle_d, double angle_f);

ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, int partie);

ei_linked_point_t* rounded_frame_tot(ei_rect_t rect, int rayon);

ei_linked_point_t* rounded_frame_haut(ei_rect_t rect, int rayon);

ei_linked_point_t* rounded_frame_bas(ei_rect_t rect, int rayon);

#endif
