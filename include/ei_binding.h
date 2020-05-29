/**
 * @file ei_draw_annexe.h
 * @brief Fonctions servant à gérer la liste des eventtype associés à leurs traitants
 *
 * \author Created by Equipe 5 on 26.05.2020.
 */
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

typedef struct ei_linked_action_t{
    ei_action_t                 action;
    struct ei_linked_action_t*     next;
} ei_linked_action_t;

typedef struct ei_linked_event_t{
    ei_eventtype_t              eventtype;
    ei_linked_action_t*          l_action;
    struct ei_linked_event_t*    next;
} ei_linked_event_t;

extern ei_linked_event_t *l_event;

/**
 * \brief Permets d'insérer les types d'événements liés à leurs traitants dans une liste en paramètre global
 *
 * @param eventtype type de l'événement
 * @param widget Widget à associer
 * @param tag Tag à associer
 * @param callback Traitant à associer
 * @param user_param Paramètres à associer
 */
void insere_binding(ei_eventtype_t		eventtype,
                    ei_widget_t*		widget,
                    ei_tag_t		tag,
                    ei_callback_t		callback,
                    void*			user_param);

/**
 * \brief Renvoie une nouvelle ei_linked_action_t*
 *
 * @param widget
 * @param tag
 * @param callback
 * @param user_param
 * @return
 */
ei_linked_action_t* new_action(ei_widget_t*		widget,
                              ei_tag_t		tag,
                              ei_callback_t		callback,
                              void*			user_param);

/**
 * \brief Ressort l'événement concerné par le type d'événement dans la liste des événements liés aux traitants
 * @param eventtype
 * @return
 */
ei_linked_event_t* trouve_event(ei_eventtype_t eventtype);

/**
 * \brief Insère une action dans une liste chaînée d'actions
 *
 * @param l_action
 * @param widget
 * @param tag
 * @param callback
 * @param user_param
 */
void insere_action(ei_linked_action_t** l_action,
                   ei_widget_t*		widget,
                   ei_tag_t		tag,
                   ei_callback_t		callback,
                   void*			user_param);

/**
 * \brief Vérifie si une action est la même que celle passée par paramètres
 *
 * @param action
 * @param widget
 * @param tag
 * @param callback
 * @param user_param
 * @return
 */
ei_bool_t meme_action(ei_linked_action_t* action,
                      ei_widget_t*		  widget,
                      ei_tag_t		      tag,
                      ei_callback_t		  callback,
                      void*			      user_param);

#endif //PROJETC_IG_EI_BINDING_H
