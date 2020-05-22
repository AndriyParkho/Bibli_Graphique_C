/**
 * @file ei_draw_annexe.c
 * @brief Fonctions servant à dessiner les widgets et leurs détails
 *
 * \author Created by Equipe 5 on 21.05.2020.
 */

#include "ei_draw_annexe.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

/*
 * Fonction qui génère une liste de points définissant un arc,paramétrée par le centre, le rayon,
 * et les angles de début et fin de l’arc
 */
ei_linked_point_t * arc(ei_point_t centre, int rayon, double angle_d, double angle_f){
        double pas = (angle_d - angle_f )/ 10;
        ei_linked_point_t* points = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t*));
        ei_linked_point_t* cour = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t*));
        ei_point_t coord;
        int i;
        double angle_suivant;
        points->point.x = centre.x + (int)(rayon * cos(angle_d));
        points->point.y = centre.y - (int)(rayon * sin(angle_d));
        cour = points;
        for (i = 1; i < 11; i++){
                angle_suivant = angle_d - pas*i;
                coord.x = centre.x + (int)(rayon * cos(angle_suivant));
                coord.y = centre.y - (int)(rayon * sin(angle_suivant));
                cour->next = cree_element_point(coord);
                cour = cour->next;
        }
        return points;
}

ei_linked_point_t* cree_element_point(ei_point_t coord) {
        ei_linked_point_t* l_point = (ei_linked_point_t*)malloc(sizeof(ei_linked_point_t*));
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
        dernier_point->next = arc(centre, r, 0, 3*M_PI/2);
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
        return points;
}