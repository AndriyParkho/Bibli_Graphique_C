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

ei_linked_point_t* cree_element_point(ei_point_t coord);

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
ei_linked_point_t* rounded_frame(ei_rect_t rect, int rayon, int partie);

/**
 * \brief Fonction permettant de générer une liste de point définissant un cadre aux bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame_tot(ei_rect_t rect, int rayon);

/**
 * \brief Fonction permettant de générer une liste de point définissant la partie haute d'un cadre aux
 *        bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame_haut(ei_rect_t rect, int rayon);

/**
 * \brief Fonction permettant de générer une liste de point définissant la partie basse d'un cadre aux
 *        bords arrondis
 *
 * @param rect      Rectangle définissant le cadre
 * @param rayon     Le rayon des angles
 *
 * @return Une liste chainée de points définissants la forme demandée
 */
ei_linked_point_t* rounded_frame_bas(ei_rect_t rect, int rayon);

#endif
