/**
 * @file ei_draw_annexe.h
 * @brief Fonctions servant à dessiner les widgets et leurs détails
 *
 * \author Created by Equipe 5 on 21.05.2020.
 */


#ifndef EI_DRAW_ANNEXE_H
#define EI_DRAW_ANNEXE_H

#include <ei_widgettypes.h>
#include "ei_draw.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#define min(a,b) (a<=b?a:b)

ei_surface_t static root_offscreen;

ei_surface_t get_root_offscreen();

void set_root_offscreen(ei_surface_t surface);
/**
 * \brief Génère une liste de quatre points définissant un rectangle.
 *
 * @param       coord_x         Coordonnées en x des points
 * @param       coord_y         Coordonnées en y des points
 * @param       border_width    Epaisseur du contour à soustraire au rectangle (utile lorsqu'il y a un relief)
 *
 * @return      Une liste chainée de quatre points définissants un rectangle
 */
ei_linked_point_t * rectangle(int coord_x[], int coord_y[], int border_width);

/**
 * \brief Génère une couleur plus sombre ou plus claire que celle donnée en entrée.
 *
 * @param       frame           Un widget frame
 * @param       variation       Valeur correspondant à la variation de couleur souhaité
 *
 * @return      Une couleur de type ei_color_t
 */
ei_color_t color_variation(ei_frame_t* frame, int variation);

/**
 * \brief Génère et affiche deux polygones de couleurs différentes pour créer un effet de relief.
 *
 * @param       widget       Widget de type frame
 * @param       points       Liste de points caractérisant un rectangle
 * @param       surface      Correspond à ei_app_root_surface()
 *
 * @return      void
 */
void draw_polygons_relief(ei_widget_t* widget, ei_linked_point_t points[4], ei_surface_t surface);

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
