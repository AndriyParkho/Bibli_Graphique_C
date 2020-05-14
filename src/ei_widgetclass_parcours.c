/*
 * Fonctions parcourant la liste chainée des widgetclass
 */


void insere_class_queue(ei_widgetclass_t **list, ei_widgetclass_t* widgetclass){
        // Si la liste est vide on ajoute en tête la nouvelle classe...
        if (*list == NULL){
                *list = widgetclass;
        }  else{ // ..Sinon on parcourt la liste jusqu'à tomber sur la queue
                ei_widgett_class *class_courante = *list;
                while( class_courante->next != NULL){
                        class_courante = class_courante->next;
                }
                class_courante->next = widgetclass;
        }
}