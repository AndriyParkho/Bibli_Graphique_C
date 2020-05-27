/*
 * Fonctions parcourant la liste chainée des widgetclass
 */

#include "ei_widgetclass_parcours.h"

ei_widgetclass_t *class_tete = NULL;


/**
 * \brief Fonction qui ajoute une nouvelle widgetclass à la liste chainée des widgetclass passée en
 * paramètre
 *
 * @param list           un pointeur sur la liste chaînée des geometrymanager
 * @param widgetclass    un pointeur sur la widgetclass que l'on veut ajouter à la liste
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


/**
 * \brief Fonction qui retourne la widgetclass dont on connaît le nom passé en paramètre, renvoie NULL si
 *        on ne le trouve pas
 *
 * @param list  Pointeur sur la liste chaînée que l'on veut consulter
 * @param name  Le nom de la widgetclass que l'on recherche
 *
 * @return Une structure qui décrit la widgetclass recherchée
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

/**
 * \brief Fonction qui permet de parcourir l'arbre de hierarchie des widget en profondeur, et de les dessiner,
 *        depuis la racine passée en paramètre
 *
 * @param root          Le widget racine de l'arbre de hiérarchie de widget que l'on souhaite dessiner
 * @param root_widget   La surface sur laquelle on souhaite dessiner les widgets
 */
void ei_parcours_profondeur_widget(ei_widget_t* root, ei_surface_t root_widget) {
    root->wclass->drawfunc(root, root_widget, root_widget, NULL);
    if (root->children_head) ei_parcours_profondeur_widget(root->children_head, &root->screen_location);
    if (root->next_sibling) ei_parcours_profondeur_widget(root->next_sibling, &root->screen_location);
}

/**
 * \brief Fonction permettant d'ajouter un widget enfant à un widget parent
 *
 * @param parent    Widget parent
 * @param child     Widget enfant
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

/**
 * \brief Fonction qui permet de parcourir l'arbre de hierarchie des widget en profondeur, et libérer la mémoire qu'ils occupent,
 *        depuis la racine passée en paramètre
 *
 * @param root          Le widget racine de l'arbre de hiérarchie de widget que l'on souhaite libérer
 */
void ei_parcours_profondeur_free_widget(ei_widget_t* root) {
        if (root->children_head) ei_parcours_profondeur_free_widget(root->children_head);
        if (root->next_sibling) ei_parcours_profondeur_free_widget(root->next_sibling);
        root->wclass->releasefunc(root);
}


/**
 * \brief Fonction qui libère la mémoire allouée pour la liste chainée des widgetclass
 *
 * @param list           un pointeur sur la tête de la liste chainée des widget class
 */
void free_class(ei_widgetclass_t *list){
        // Si la liste est vide on ne fait rien...
        if (list == NULL){
                // Y a rien à faire
        } else if(list->next == NULL)
                free(list); // On libère la tête de liste
        else{
                free_class(list->next);
                free(list);
        }
}

void ei_parcours_profondeur_callback(ei_widget_t* root, ei_callback_t callback, ei_tag_t tag, ei_event_t* event, void* user_param) {
        if (strcmp(tag, "all") == 0 || strcmp(root->wclass->name, tag)==0) {
                callback(root, event, user_param);
        }
        if (root->children_head) ei_parcours_profondeur_callback(root->children_head, callback, tag, event, user_param);
        if (root->next_sibling) ei_parcours_profondeur_callback(root->next_sibling, callback, tag, event, user_param);
}