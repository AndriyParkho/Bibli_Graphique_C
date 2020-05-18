/*
 * Fonctions parcourant la liste chainée des widgetclass
 */

#include "ei_widgetclass_parcours.h"

ei_widgetclass_t *class_tete = NULL;


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

void ei_parcours_profondeur_widget(ei_widget_t* root, ei_surface_t root_widget) {
    root->wclass->drawfunc(root, root_widget, root_widget, NULL);
    if (root->children_head) ei_parcours_profondeur_widget(root->children_head, &root->screen_location);
    if (root->next_sibling) ei_parcours_profondeur_widget(root->next_sibling, &root->screen_location);
}

/*
 * Fonction qui ajoute un widget enfant à un widget parent
 */
void add_widget_child(struct ei_widget_t* parent, struct ei_widget_t* child){
        // Si le parent n'a pas d'enfant à la base on place child comme head et tail
        if(parent->children_head == NULL){
                parent->children_head = child;
                parent->children_tail = child;
        } else{
                parent->children_tail->next_sibling = child;
                parent->children_tail = child;
        }
}