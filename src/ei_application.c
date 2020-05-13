#include "../include/ei_application.h"
#include <stdio.h>
#include "ei_event.h"

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
    hw_init();
    hw_create_window(main_window_size, fullscreen);
}

void ei_app_free(void) {
}

void ei_app_run(void) {
    ei_event_t	event;
    event.type = ei_ev_none;
    while (event.type != ei_ev_keydown)
        hw_event_wait_next(&event);
}

void ei_app_invalidate_rect(ei_rect_t* rect) {

}

void ei_app_quit_request(void) {

}

ei_widget_t* ei_app_root_widget(void) {
        return NULL;
}

ei_surface_t ei_app_root_surface(void) {
        return NULL;
}