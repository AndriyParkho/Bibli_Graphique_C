/**
 *  @file	ei_widgetclass_parcours.h
 *  @brief	Gère les différentes fonctions qui permettent de traiter et parcourir les listes de widgetclass
 *
 *  \author Created by Equipe 5 on 14.05.2020.
 */

#ifndef EI_WIDGETCLASS_PARCOURS_H
#define EI_WIDGETCLASS_PARCOURS_H

#include <stdbool.h>
#include <string.h>
#include "ei_widgetclass.h"
#include "ei_widget.h"
#include <stdlib.h>
#include "ei_event.h"

extern ei_widgetclass_t *class_tete;

/*
 * Fonction qui ajoute une nouvelle widgetclass à la liste chainée des widgetclass
 */
void insere_class_queue(ei_widgetclass_t **list, ei_widgetclass_t* widgetclass);


/*
 * Fonction qui retourne la widgetclass dont on connaît le nom et dont on a besoin
 */
ei_widgetclass_t* trouve_class(ei_widgetclass_t **list, ei_widgetclass_name_t name);

void ei_parcours_profondeur_widget(ei_widget_t* root, ei_surface_t root_widget);

/*
 * Fonction qui ajoute un widget enfant à un widget parent
 */
void add_widget_child(struct ei_widget_t* parent, struct ei_widget_t* child);

/**
 * \brief Fonction qui permet de parcourir l'arbre de hierarchie des widget en profondeur, et libérer la mémoire qu'ils occupent,
 *        depuis la racine passée en paramètre
 *
 * @param root          Le widget racine de l'arbre de hiérarchie de widget que l'on souhaite libérer
 */
void ei_parcours_profondeur_free_widget(ei_widget_t* root);

/**
 * \brief Fonction qui libère la mémoire allouée pour la liste chainée des widgetclass
 *
 * @param list           un pointeur sur la tête de la liste chainée des widget class
 */
void free_class(ei_widgetclass_t *list);

void ei_parcours_profondeur_callback(ei_widget_t* root, ei_callback_t callback, ei_tag_t tag, ei_event_t* event, void* user_param);

#endif //EI_WIDGETCLASS_PARCOURS_H
