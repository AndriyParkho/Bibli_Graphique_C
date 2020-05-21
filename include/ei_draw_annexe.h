/**
 * @file ei_draw_annexe.h
 * @brief Fonctions servant à dessiner les widgets et leurs détails
 *
 * \author Created by Equipe 5 on 21.05.2020.
 */


#ifndef EI_DRAW_ANNEXE_H
#define EI_DRAW_ANNEXE_H

#include "ei_draw.h"

ei_linked_point_t * arc(ei_point_t centre, int rayon, double angle_d, double angle_f);

/**
 * \brief Fonction permettant de générer une liste de point définissant soit un cadre aux bords arrondis,
 *        sa partiehaute ou sa partie basse
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 * @param partie    Paramètre définissant si on génère la totalité de la forme, la partie haute ou la partie
 *                  basse
 *
 * @return  Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, int partie);

ei_linked_point_t* rounded_frame_tot(ei_rect_t rect, int rayon);

ei_linked_point_t* rounded_frame_haut(ei_rect_t rect, int rayon);

ei_linked_point_t* rounded_frame_bas(ei_rect_t rect, int rayon);

#endif
