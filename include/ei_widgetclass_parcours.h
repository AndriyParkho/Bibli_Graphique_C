//
// Created by andriy on 14/05/2020.
//

#include "ei_widgetclass.h"

#ifndef EI_WIDGETCLASS_PARCOURS_H
#define EI_WIDGETCLASS_PARCOURS_H

/*
 * Fonction qui ajoute une nouvelle widgetclass à la liste chainée des widgetclass
 */
void insere_class_queue(ei_widgetclass_t **list, ei_widgetclass_t* widgetclass);


/*
 * Fonction qui retourne la widgetclass dont on connaît le nom et dont on a besoin
 */
ei_widgetclass_t* trouve_class(ei_widgetclass_t **list, ei_widgetclass_name_t name);

#endif //EI_WIDGETCLASS_PARCOURS_H
