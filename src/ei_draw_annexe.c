/**
 * @file ei_draw_annexe.c
 * @brief Fonctions servant à dessiner les widgets et leurs détails
 *
 * \author Created by Equipe 5 on 21.05.2020.
 */


#include "ei_draw_annexe.h"


/**
 * \brief Génère une liste de quatre points définissant un rectangle.
 *
 * @param       coord_x         Coordonnées en x des points
 * @param       coord_y         Coordonnées en y des points
 * @param       border_width    Epaisseur du contour à soustraire au rectangle (utile lorsqu'il y a un relief)
 *
 * @return Une liste chainée de quatre points définissants un rectangle
 */
ei_linked_point_t * rectangle(int coord_x[], int coord_y[], int border_width){
        int i = 0;
        ei_linked_point_t* points = (ei_linked_point_t*)calloc(4, sizeof(ei_linked_point_t));
        while (i != 4) {
                switch (i) {
                        case 0 :
                                points[i].point.x = coord_x[0] + border_width;
                                points[i].point.y = coord_y[0] + border_width;
                                break;
                        case 1 :
                                points[i].point.x = coord_x[1] - border_width;
                                points[i].point.y = coord_y[0] + border_width;
                                break;
                        case 2 :
                                points[i].point.x = coord_x[1] - border_width;
                                points[i].point.y = coord_y[1] - border_width;
                                break;
                        case 3 :
                                points[i].point.x = coord_x[0] + border_width;
                                points[i].point.y = coord_y[1] - border_width;
                                break;
                }
                if (i < 3) points[i].next = &points[i + 1];
                else points[i].next = NULL;
                i++;
        }
        return points;
}

/**
 * \brief Génère une couleur plus sombre ou plus claire que celle donnée en entrée.
 *
 * @param       frame           Un widget frame
 * @param       variation       Valeur correspondant à la variation de couleur souhaité
 *
 * @return      Une couleur de type ei_color_t
 */
ei_color_t color_variation(ei_frame_t* frame, int variation){
        ei_color_t new_color = {frame->color.red + variation, frame->color.green + variation,
                                frame->color.blue + variation, frame->color.alpha};
        return new_color;
}

/**
 * \brief Génère et affiche deux polygones de couleurs différentes pour créer un effet de relief.
 *
 * @param       widget       Widget de type frame
 * @param       points       Liste de points caractérisant un rectangle
 * @param       surface      Correspond à ei_app_root_surface()
 *
 * @return      void
 */
void draw_polygons_relief(ei_widget_t* widget, ei_linked_point_t points[4], ei_surface_t surface) {
        int half_length = widget->screen_location.size.height / 2;
        ei_frame_t* frame = (ei_frame_t*)widget;
        ei_linked_point_t points_sup[5];
        ei_linked_point_t points_inf[5];
        ei_color_t dark_color = color_variation(frame, -30);
        ei_color_t light_color = color_variation(frame, 30);
        int i = 0;
        while (i != 5) {
                switch (i) {
                        case 0 :
                        case 1 :
                                points_sup[i] = points[i];
                                points_inf[i] = points[i + 1];
                                break;
                        case 2 :
                                points_sup[i].point.x = points[i].point.x - half_length;
                                points_sup[i].point.y = points[i].point.y - half_length;
                                points_inf[i] = points[i + 1];
                                break;
                        case 3 :
                                points_sup[i].point.x = points[i].point.x + half_length;
                                points_sup[i].point.y = points[i].point.y - half_length;
                                points_inf[i].point.x = points[i].point.x + half_length;
                                points_inf[i].point.y = points[i].point.y - half_length;
                                break;
                        case 4 :
                                points_sup[i] = points[i - 1];
                                points_inf[i].point.x = points[i - 2].point.x - half_length;
                                points_inf[i].point.y = points[i - 2].point.y - half_length;
                                break;
                }
                if (i < 4) points_sup[i].next = &points_sup[i + 1];
                else points_sup[i].next = NULL;
                if (i < 4) points_inf[i].next = &points_inf[i + 1];
                else points_inf[i].next = NULL;
                i++;
        }
        if (frame->relief == ei_relief_raised) {
                ei_draw_polygon(surface, points_sup, light_color, &(widget->screen_location));
                ei_draw_polygon(surface, points_inf, dark_color, &(widget->screen_location));
        } else { // cad frame->relief == ei_relief_sunken
                ei_draw_polygon(surface, points_sup, dark_color, &(widget->screen_location));
                ei_draw_polygon(surface, points_inf, light_color, &(widget->screen_location));
        }
}

/*
 * Fonction qui génère une liste de points définissant un arc,paramétrée par le centre, le rayon,
 * et les angles de début et fin de l’arc
 */
ei_linked_point_t * arc(ei_point_t centre, int rayon, double angle_d, double angle_f){
        int nb_points = 10;
        double pas = (angle_d - angle_f )/nb_points;
        ei_linked_point_t* points = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
        ei_linked_point_t* cour;
        ei_point_t coord;
        int i;
        double angle_suivant;
        points->point.x = centre.x + (int)(rayon * cos(angle_d));
        points->point.y = centre.y - (int)(rayon * sin(angle_d));
        cour = points;
        for (i = 1; i <= nb_points ; i++){
                angle_suivant = angle_d - pas*i;
                coord.x = centre.x + (int)(rayon * cos(angle_suivant));
                coord.y = centre.y - (int)(rayon * sin(angle_suivant));
                cour->next = cree_element_point(coord);
                cour = cour->next;
        }
        return points;
}

ei_linked_point_t* cree_element_point(ei_point_t coord) {
        ei_linked_point_t* l_point = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t        ));
        l_point->point.x = coord.x;
        l_point->point.y = coord.y;
        l_point->next = NULL;
        return l_point;
}

/**
 * \brief Fonction permettant de générer une liste de point définissant soit un cadre aux bords arrondis,
 *        sa partie haute ou sa partie basse.
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 * @param partie    Paramètre définissant si on génère la totalité de la forme, la partie haute ou la partie
 *                  basse. Ce paramètre vaut :
 *                      <ul>
 *                          <li> 0 quand on souhaite générer la totalité de la forme
 *                          <li> 1 quand on souhaite générer la partie haute de la forme
 *                          <li> 2 quand on souhaite générer la partie basse de la forme
 *                      </ul>
 *
 * @return  Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame(ei_rect_t rect, int r, int partie) {
        assert(partie>=0 && partie<=2);
        switch (partie) {
                case 0 : return(rounded_frame_tot(rect,r));
                case 1 : return(rounded_frame_haut(rect,r));
                case 2 : return(rounded_frame_bas(rect,r));
                default : printf("Ce cas n'arrivera jamais\n");
        }
}

/**
 * \brief Fonction permettant de générer une liste de point définissant un cadre aux bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
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
        dernier_point->next = arc(centre, r, 2*M_PI, 3*M_PI/2);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = centre.x - (rect.size.width - 2*r);
        dernier_point->next = arc(centre, r, 3*M_PI/2, M_PI);
        return points;
}

/**
 * \brief Fonction permettant de générer une liste de point définissant la partie haute d'un cadre aux
 *        bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame_haut(ei_rect_t rect, int r) {
        ei_linked_point_t* points;
        ei_linked_point_t* dernier_point;
        ei_point_t centre;
        int h = min(rect.size.width/2, rect.size.height/2);
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

        centre.x = rect.top_left.x + rect.size.width - h;
        centre.y = rect.top_left.y + h;
        dernier_point->next = cree_element_point(centre);
        dernier_point = dernier_point->next;

        centre.x = rect.top_left.x + h;
        centre.y = rect.top_left.y + rect.size.height - h;
        dernier_point->next = cree_element_point(centre);
        dernier_point = dernier_point->next;

        centre.x = rect.top_left.x + r;
        centre.y = rect.top_left.y + rect.size.height - r;
        dernier_point->next = arc(centre,r,5*M_PI/4,M_PI);
        return points;
}

/**
 * \brief Fonction permettant de générer une liste de point définissant la partie basse d'un cadre aux
 *        bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame_bas(ei_rect_t rect, int r) {
        ei_linked_point_t* points;
        ei_linked_point_t* dernier_point;
        ei_point_t centre;
        int h = min(rect.size.width/2, rect.size.height/2);
        centre.x = rect.top_left.x + rect.size.width - r;
        centre.y = rect.top_left.y + r;
        points = arc(centre, r, M_PI/4, 0);
        dernier_point = points;
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.y = centre.y + (rect.size.height - 2*r);
        dernier_point->next = arc(centre, r, 2*M_PI, 3*M_PI/2);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }
        centre.x = rect.top_left.x + r;
        dernier_point->next = arc(centre, r, 3*M_PI/2, 5*M_PI/4);
        while (dernier_point->next) {
                dernier_point = dernier_point->next;
        }

        centre.x = rect.top_left.x + h;
        centre.y = rect.top_left.y + rect.size.height - h;
        dernier_point->next = cree_element_point(centre);
        dernier_point = dernier_point->next;

        centre.x = rect.top_left.x + rect.size.width - h;
        centre.y = rect.top_left.y + h;
        dernier_point->next = cree_element_point(centre);
        return points;
}