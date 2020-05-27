//
// Created by Enora on 26/05/2020.
//

#ifndef PROJETC_IG_EI_BINDING_H
#define PROJETC_IG_EI_BINDING_H

#include "ei_event.h"
#include "ei_types.h"
#include <stdlib.h>
#include <string.h>



typedef struct {
    ei_callback_t       callback;
    ei_widget_t*        widget;
    ei_tag_t            tag;
    void*               user_param;
} ei_action_t;

typedef struct {
    ei_action_t                 action;
    struct ei_linked_action*     next;
} ei_linked_action_t;

typedef struct {
    ei_eventtype_t              eventtype;
    ei_linked_action_t*          l_action;
    struct ei_linked_event_t*    next;
} ei_linked_event_t;

extern ei_linked_event_t *l_event = NULL;

void insere_binding(ei_eventtype_t		eventtype,
                    ei_widget_t*		widget,
                    ei_tag_t		tag,
                    ei_callback_t		callback,
                    void*			user_param);

ei_linked_action_t* new_action(ei_widget_t*		widget,
                              ei_tag_t		tag,
                              ei_callback_t		callback,
                              void*			user_param);

ei_linked_event_t* trouve_event(ei_eventtype_t eventtype);

void insere_action(ei_linked_action_t* l_action,
                   ei_widget_t*		widget,
                   ei_tag_t		tag,
                   ei_callback_t		callback,
                   void*			user_param);

#endif //PROJETC_IG_EI_BINDING_H
