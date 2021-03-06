//
// Created by Enora on 26/05/2020.
//

#include "ei_event.h"
#include <assert.h>
#include "ei_binding.h"

/**
 * \brief	Binds a callback to an event type and a widget or a tag.
 *
 * @param	eventtype	The type of the event.
 * @param	widget		The callback is only called if the event is related to this widget.
 *				This parameter must be NULL if the "tag" parameter is not NULL.
 * @param	tag		The callback is only called if the event is related to a widget that
 *				has this tag. A tag can be a widget class name, or the tag "all".
 *				This parameter must be NULL is the "widget" parameter is not NULL.
 * @param	callback	The callback (i.e. the function to call).
 * @param	user_param	A user parameter that will be passed to the callback when it is
 *				called.
 */
void		ei_bind			(ei_eventtype_t		eventtype,
                                ei_widget_t*		widget,
                                ei_tag_t		tag,
                                ei_callback_t		callback,
                                void*			user_param) {
        assert(!(widget==NULL && tag == NULL));
        insere_binding(eventtype, widget, tag, callback, user_param);
}

void    ei_unbind(ei_eventtype_t		eventtype,
                  ei_widget_t*		widget,
                  ei_tag_t		tag,
                  ei_callback_t		callback,
                  void*			user_param) {
        ei_linked_event_t* ev_cherche = trouve_event(eventtype);
        ei_linked_action_t* ac_cour = ev_cherche->l_action;
        ei_linked_action_t* ac_pred = NULL;
        if (meme_action(ev_cherche->l_action, widget,tag,callback,user_param)) {
                ev_cherche->l_action = ac_cour->next;
        }
        else {
                ac_pred = ac_cour;
                ac_cour = ac_cour->next;
                while (!meme_action(ac_cour, widget, tag, callback, user_param)) {
                        ac_pred = ac_cour;
                        ac_cour = ac_cour->next;
                }
                ac_pred = ac_cour->next;
        }
        free(ac_cour);
        ac_cour->next = NULL;
}