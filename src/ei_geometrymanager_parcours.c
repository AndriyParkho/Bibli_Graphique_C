//
// Created by andriy on 18/05/2020.
//

#include "ei_geometrymanager_parcours.h"

ei_geometrymanager_t *geometrymanager_tete = NULL;


/*
 * Fonction qui ajoute une nouveau geometrymanager à la liste chainée des geometrymanager
 */
void inserer_geometrymanager_queue(ei_geometrymanager_t **list, ei_geometrymanager_t* geomanager){
        // Si la liste est vide on ajoute en tête la nouvelle geomanagere...
        if (*list == NULL){
                *list = geomanager;
        }  else{ // ..Sinon on parcourt la liste jusqu'à tomber sur la queue
                ei_geometrymanager_t *manager_courant = *list;
                while( manager_courant->next != NULL){
                        manager_courant = manager_courant->next;
                }
                manager_courant->next = geomanager;
        }
}


/*
 * Fonction qui retourne le geometrymanager dont on connaît le nom et dont on a besoin
 */
ei_geometrymanager_t* trouve_geomanager(ei_geometrymanager_t **list, ei_geometrymanager_name_t name){
        // Si la liste est vide on renvoie NULL...
        if (*list == NULL){
                return NULL;
        }
        ei_geometrymanager_t *geomanager_courant = *list;
        bool geomanager_trouve = (strcmp((char*)name, (char*)geomanager_courant->name) == 0);
        while(!geomanager_trouve && geomanager_courant->next != NULL){
                geomanager_courant = geomanager_courant->next;
                geomanager_trouve = (strcmp((char*)name, (char*)geomanager_courant->name) == 0);
        }
        if (geomanager_trouve){
                return geomanager_courant;
        }
        return NULL;
}


