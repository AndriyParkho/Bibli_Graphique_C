#include "ei_application.h"
#include <stdio.h>
#include "ei_widgettypes.h"
#include <ei_geometrytypes.h>
#include "ei_widgetclass_parcours.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager_parcours.h"
#include "ei_event.h"
#include "ei_binding.h"
#include "ei_draw_annexe.h"


ei_surface_t static root_widget;
ei_surface_t static root_offscreen;
static ei_widget_t* frame_root_widget = NULL;
static ei_bool_t quit = EI_FALSE;

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
        hw_init();
        root_widget = hw_create_window(main_window_size, fullscreen);
        set_root_offscreen(hw_surface_create(root_widget, main_window_size, EI_TRUE));
        ei_register_placer_manager();
        ei_frame_register_class();
        ei_button_register_class();
        ei_app_root_widget();
}

void ei_app_free(void) {
        ei_parcours_profondeur_free_widget(frame_root_widget);
        free_class(class_tete);
        free_geometrymanager(geometrymanager_tete);
        hw_quit();
}

void ei_app_run(void) {
        ei_event_t event;
        ei_linked_event_t* e_cour;
        ei_linked_action_t* a_cour;
        event.type = ei_ev_none;
        while (!quit) {
                // ei_parcours_profondeur_widget(frame_root_widget, root_widget);
                frame_root_widget->wclass->drawfunc(ei_app_root_widget(), ei_app_root_surface(), get_root_offscreen(), frame_root_widget->content_rect);
                hw_surface_update_rects(ei_app_root_surface(), NULL);
                hw_event_wait_next(&event);
                /*
                if (event.type == ei_ev_mouse_buttondown) {
                        ei_point_t where = event.param.mouse.where;
                        ei_button_t* ev_widget = (ei_button_t*)ei_widget_pick(&where);
                        ev_widget->callback(ev_widget, &event, ev_widget->user_param);
                }
                 */
                e_cour = trouve_event(event.type);
                if (e_cour) {
                        a_cour = e_cour->l_action;
                        while (a_cour) {
                                if (a_cour->action.widget) {
                                        a_cour->action.callback(a_cour->action.widget, &event, a_cour->action.user_param);
                                }
                                else {
                                        ei_parcours_profondeur_callback(frame_root_widget, a_cour->action.callback, a_cour->action.tag, &event, a_cour->action.user_param);
                                }
                                a_cour = a_cour->next;
                        }
                }
        }
}

void ei_app_invalidate_rect(ei_rect_t* rect) {

}

void ei_app_quit_request(void) {
        quit = EI_TRUE;
}

ei_widget_t* ei_app_root_widget(void) {
        if (frame_root_widget){
                return frame_root_widget;
        }
        ei_widgetclass_t *frame_widgetclass = ei_widgetclass_from_name("frame");
        frame_root_widget = (ei_widget_t*)frame_widgetclass->allocfunc();
        frame_root_widget->wclass = frame_widgetclass;
        frame_root_widget->wclass->setdefaultsfunc(frame_root_widget);

        frame_root_widget->pick_id = 0;
        ei_color_t* pick_color = malloc(sizeof(ei_color_t));
        ei_color_t color = {0x00, 0x00, 0x00, 0x00};
        *pick_color = color;
        frame_root_widget->pick_color = pick_color;

        /* Widget Hierachy Management */
        frame_root_widget->parent = NULL;
        frame_root_widget->children_head = NULL;
        frame_root_widget->children_tail = NULL;
        frame_root_widget->next_sibling = NULL;
        /* Geometry Management */
        frame_root_widget->geom_params = NULL;
        frame_root_widget->requested_size = hw_surface_get_size(root_widget);
        frame_root_widget->screen_location = hw_surface_get_rect(root_widget);
        frame_root_widget->content_rect = &(frame_root_widget->screen_location);
        return frame_root_widget;
}

ei_surface_t ei_app_root_surface(void) {
        return root_widget;
}