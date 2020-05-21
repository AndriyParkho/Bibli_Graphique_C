/*
 * Fonctions servant à dessiner les widgets et leurs détails
 */

#include "ei_draw_annexe.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>


ei_linked_point_t * arc(ei_point_t centre, int rayon, double angle_d, double angle_f){

}

ei_linked_point_t* rounded_frame(ei_rect_t rect, int r, int partie) {
        assert(partie>=0 && partie<=2);
        switch (partie) {
                case 0 : return(rounded_frame_tot(rect,r));
                case 1 : return(rounded_frame_haut(rect,r));
                case 2 : return(rounded_frame_bas(rect,r));
        }
}

ei_linked_point_t* rounded_frame_tot(ei_rect_t rect, int r) {
        ei_linked_point_t* points;
        ei_linked_point_t* dernier_point;
        ei_point_t centre;
        centre.x = rect.top_left.x + r;
        centre.y = rect.top_left.y + r;
        points = arc(centre, r, M_PI, M_PI/2);
        dernier_point = points;
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = centre.x + (rect.size.width - 2*r);
        dernier_point->next = arc(centre, r, M_PI/2, 0);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.y = centre.y + (rect.size.height - 2*r);
        dernier_point->next = arc(centre, r, 0, 3*M_PI/2);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = rect.top_left.x + r;
        dernier_point->next = arc(centre, r, 3*M_PI/2, M_PI);
        return(points);
}

ei_linked_point_t* rounded_frame_haut(ei_rect_t rect, int r) {
        ei_linked_point_t points;
        ei_linked_point_t* dernier_point;
        ei_point_t centre;
        centre.x = rect.top_left.x + r;
        centre.y = rect.top_left.y + r;
        points = arc(centre, r, M_PI, M_PI/2);
        dernier_point = points;
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = centre.x + (rect.size.width - 2*r);
        dernier_point->next = arc(centre, r, M_PI/2, M_PI/4);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = rect.top_left.x + r;
        centre.y = centre.y + (rect.size.height - 2*r);
        dernier_point->next = arc(centre,r,5*M_PI/4,M_PI);
        return(points);
}

ei_linked_point_t* rounded_frame_bas(ei_rect_t rect, int r) {
        ei_linked_point_t* points;
        ei_linked_point_t* dernier_point;
        ei_point_t centre;
        centre.x = rect.top_left.x + rect.size.width - r;
        centre.y = rect.top_left.y + r;
        points = arc(centre, r, M_PI/4, 0);
        dernier_point = points;
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.y = centre.y + (rect.size.height - 2*r);
        dernier_point->next = arc(centre, r, 0, 3*M_PI/2);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = rect.top_left.x + r;
        dernier_point->next = arc(centre, r, 3*M_PI/2, 5*M_PI/4);
        return(points);
}