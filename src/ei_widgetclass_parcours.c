/*
 * Fonctions parcourant la liste chainée des widgetclass
 */


void insere_class_queue(ei_widgetclass_t **list, ei_widgetclass_t* widgetclass){
        ei_widget_class *new_class = widgetclass->allocfunc();
        new_class->name = widgetclass->name;
        new_class->allocfunc = widgetclass->allocfunc;
        new_class->releasefunc = widgetclass->releasefunc;
        new_class->drawfunc = widgetclass->drawfunc;
        new_class->setdefaultsfunc = widgetclass->setdefaultsfunc;
        new_class->geomnotifyfunc = widgetclass->geomnotifyfunc;
        new_class->next = NULL;
        // Si la liste est vide on ajoute en tête la nouvelle classe...
        if (*list == NULL){
                *list = new_class;
        }  else{ // ..Sinon on parcourt la liste jusqu'à tomber sur la queue
                ei_widgett_class *class_courante = *list;
                while( class_courante->next != NULL){
                        class_courante = class_courante->next;
                }
                class_courante->next = new_class;
        }
}