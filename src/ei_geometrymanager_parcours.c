//
// Created by andriy on 18/05/2020.
//

#include "ei_geometrymanager_parcours.h"

ei_geometrymanager_t *geometrymanager_tete = NULL;


/**
 * \brief Fonction qui ajoute un nouveau geometrymanager à la liste chainée des geometrymanager passée en
 * paramètre
 *
 * @param list          un pointeur sur la liste chaînée des geometrymanager
 * @param geomanager    un pointeur sur le geometrymanager que l'on veut ajouter à la liste
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


/**
 * \brief Fonction qui retourne le geometrymanager dont on connaît le nom passé en paramètre, renvoie NULL si
 *        on ne le trouve pas
 *
 * @param list  Pointeur sur la liste chaînée que l'on veut consulter
 * @param name  Le nom du geometrymanager que l'on recherche
 *
 * @return Une structure qui décrit le geometrymanager recherché
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


/**
 * \brief Fonction qui libère la mémoire allouée pour la liste chainée des geometry manager
 *
 * @param list           un pointeur sur la tête de la liste chainée des geometry manager
 */
void free_geometrymanager(ei_geometrymanager_t *list){
        // Si la liste est vide on ne fait rien...
        if (list == NULL){
                // Y a rien à faire
        } else if(list->next == NULL)
                free(list); // On libère la tête de liste
        else{
                free_geometrymanager(list->next);
                free(list);
        }
}


