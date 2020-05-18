//
// Created by andriy on 18/05/2020.
//

#ifndef EI_GEOMETRY_REGISTER_H
#define EI_GEOMETRY_REGISTER_H

#include "ei_geometrymanager.h"

extern ei_geometrymanager_t *geometrymanager_tete;

/*
 * Fonction qui créer le geometrymanager placeur
 */
void    ei_placeur_register_manager     (void);


/*
 * Fonction qui ajoute une nouveau geometrymanager à la liste chainée des geometrymanager
 */
void inserer_geometrymanager_queue(ei_geometrymanager_t **list, ei_geometrymanager_t* geomanager);


/*
 * Fonction qui retourne le geometrymanager dont on connaît le nom et dont on a besoin
 */
ei_geometrymanager_t* trouve_geomanager(ei_geometrymanager_t **list, ei_geometrymanager_name_t name);

#endif
