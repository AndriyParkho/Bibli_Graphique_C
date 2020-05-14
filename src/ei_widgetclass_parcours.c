/*
 * Fonctions parcourant la liste chainée des widgetclass
 */

#include <stdbool.h>
#include <string.h>
#include <ei_widgetclass.h>

/*
 * Fonction qui ajoute une nouvelle widgetclass à la liste chainée des widgetclass
 */
void insere_class_queue(ei_widgetclass_t **list, ei_widgetclass_t* widgetclass){
        // Si la liste est vide on ajoute en tête la nouvelle classe...
        if (*list == NULL){
                *list = widgetclass;
        }  else{ // ..Sinon on parcourt la liste jusqu'à tomber sur la queue
                ei_widgetclass_t *class_courante = *list;
                while( class_courante->next != NULL){
                        class_courante = class_courante->next;
                }
                class_courante->next = widgetclass;
        }
}

/*
 * Fonction qui retourne la widgetclass dont on connaît le nom et dont on a besoin
 */

ei_widgetclass_t* trouve_class(ei_widgetclass_t **list, ei_widgetclass_name_t name){
        // Si la liste est vide on renvoie NULL...
        if (*list == NULL){
                return NULL;
        }
        ei_widgetclass_t *class_courante = *list;
        bool class_trouve = (strcmp((char*)name, (char*)class_courante->name) == 0);
        while(!class_trouve && class_courante->next != NULL){
                class_courante = class_courante->next;
                class_trouve = (strcmp((char*)name, (char*)class_courante->name) == 0);
        }
        if (class_trouve){
                return class_courante;
        }
        return NULL;
}