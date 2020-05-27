//
// Created by Enora on 26/05/2020.
//

#include "ei_binding.h"

ei_linked_event_t *l_event = NULL;

void insere_binding(ei_eventtype_t		eventtype,
                    ei_widget_t*		widget,
                    ei_tag_t		tag,
                    ei_callback_t		callback,
                    void*			user_param) {
        ei_linked_event_t* l_event_cour = l_event;
        if (l_event_cour==NULL) {
                l_event_cour = (ei_linked_event_t*)malloc(sizeof(ei_linked_event_t));
                l_event_cour->eventtype = eventtype;
                l_event_cour->l_action = new_action(widget, tag, callback, user_param);
                l_event_cour->next = NULL;
        }
        else {
                l_event_cour = trouve_event(eventtype);
                if (l_event_cour) {
                        insere_action(&l_event_cour->l_action, widget, tag, callback, user_param);
                }
                else {
                        l_event_cour = l_event;
                        while(l_event_cour->next) {
                                l_event_cour = l_event_cour->next;
                        }
                        ei_linked_event_t* new_event = malloc(sizeof(ei_linked_event_t));
                        new_event->eventtype = eventtype;
                        insere_action(&new_event->l_action, widget, tag, callback, user_param);
                        new_event->next = NULL;
                        l_event_cour->next = new_event;
                }
        }
}

ei_linked_action_t* new_action(ei_widget_t* widget, ei_tag_t tag, ei_callback_t callback, void* user_param) {
        ei_linked_action_t* l_action = (ei_linked_action_t*)malloc(sizeof(ei_linked_action_t));
        ei_action_t action;
        action.widget = widget;
        action.tag = tag;
        action.callback = callback;
        action.user_param = user_param;
        l_action->action = action;
        l_action->next = NULL;
        return l_action;
}

ei_linked_event_t* trouve_event(ei_eventtype_t eventtype) {
        if (l_event==NULL) {
                return NULL;
        }
        else {
                int trouve;
                ei_linked_event_t* cour = l_event;
                trouve = cour->eventtype == eventtype;
                while (!trouve && cour->next) {
                        cour = cour->next;
                        trouve = cour->eventtype == eventtype;
                }
                if (trouve) return cour;
                else return NULL;
        }
}

void insere_action(ei_linked_action_t** l_action,
                   ei_widget_t*		widget,
                   ei_tag_t		tag,
                   ei_callback_t		callback,
                   void*			user_param) {
        ei_linked_action_t* cour = *l_action;
        if (*l_action == NULL) {
                *l_action = new_action(widget, tag, callback, user_param);
        }
        else {
                while(cour->next) {
                        cour = cour->next;
                }
                cour->next = new_action(widget, tag, callback, user_param);
        }
}

