/**
 *  @file	ei_geometrymanager_placer.h
 *  @brief	Gère les différentes fonctions qui sont liées au geometrymanager de type placer
 *
 *  \author Created by Equipe 5 on 18.05.2020.
 */

#ifndef EI_GEOMETRYMANAGER_PLACER_H
#define EI_GEOMETRYMANAGER_PLACER_H

#include "ei_geometrymanager.h"
#include "ei_geometrytypes.h"
#include <string.h>
#include <stdlib.h>

/**
 * \brief	A function that runs the geometry computation for this widget. This may trigger
 *		geometry computation for this widget's parent and the other children of the parent, pour un
 *		geometrymanager de type placer
 *
 * @param	widget		The widget instance for which to compute geometry.
 */
void placer_runfunc(ei_widget_t* widget);

/**
 * \brief	A function called when a widget cease to be managed by its geometry manager.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets, pour un geometrymanager de type placer
 *
 * @param	widget		The widget instance that must be forgotten by the geometry manager.
 */
void placer_releasefunc(ei_widget_t* widget);

/**
 * \brief	Fonction qui permet de calculer le point top_left d'un rectangle selon l'ancre du widget
 *
 * @param	widget		Le widget dont il faut déterminier le point top_left
 * @param       anchor          L'ancre du widget (par défaut ei_anc_northwest)
 * @param       point           Le point dont il faut modifier les coordonées pour obtenir le point top_left
 */
ei_point_t anchor_to_topleft(ei_widget_t * widget, ei_anchor_t anchor, ei_point_t point);


#endif
