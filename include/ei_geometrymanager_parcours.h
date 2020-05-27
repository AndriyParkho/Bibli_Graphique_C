/**
 *  @file	ei_geometrymanager_parcours.h
 *  @brief	Gère les différentes fonctions qui permettent de traiter et parcourir les listes de geometrymanager
 *
 *  \author Created by Equipe 5 on 18.05.2020.
 */
#ifndef EI_GEOMETRY_REGISTER_H
#define EI_GEOMETRY_REGISTER_H

#include "ei_geometrymanager.h"
#include <stdbool.h>

/**
 * \brief Variable globale geometrymanager_tete qui pointe sur la liste des différents geometrymanager
 */
extern ei_geometrymanager_t *geometrymanager_tete;


/**
 * \brief Fonction qui ajoute un nouveau geometrymanager à la liste chainée des geometrymanager passée en
 * paramètre
 *
 * @param list          un pointeur sur la liste chaînée des geometrymanager
 * @param geomanager    un pointeur sur le geometrymanager que l'on veut ajouter à la liste
 */
void inserer_geometrymanager_queue(ei_geometrymanager_t **list, ei_geometrymanager_t* geomanager);


/**
 * \brief Fonction qui retourne le geometrymanager dont on connaît le nom passé en paramètre, renvoie NULL si
 *        on ne le trouve pas
 *
 * @param list  Pointeur sur la liste chaînée que l'on veut consulter
 * @param name  Le nom du geometrymanager que l'on recherche
 *
 * @return Une structure qui décrit le geometrymanager recherché
 */
ei_geometrymanager_t* trouve_geomanager(ei_geometrymanager_t **list, ei_geometrymanager_name_t name);


/**
 * \brief Fonction qui libère la mémoire allouée pour la liste chainée des geometry manager
 *
 * @param list           un pointeur sur la tête de la liste chainée des geometry manager
 */
void free_geometrymanager(ei_geometrymanager_t *list);

/**
 * \brief Fonction qui libère la mémoire allouée pour une liste chainée de points
 *
 * @param list           un pointeur sur la tête de la liste chainée de points
 */
void free_points(ei_linked_point_t *list);

#endif
