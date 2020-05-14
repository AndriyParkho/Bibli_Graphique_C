#include "../include/ei_application.h"
#include <stdio.h>
#include <ei_widgettypes.h>

ei_surface_t static root_widget;

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
        hw_init();
        root_widget = hw_create_window(main_window_size, fullscreen);
}

void ei_app_free(void) {
}

void ei_app_run(void) {
    getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect) {

}

void ei_app_quit_request(void) {

}

ei_widget_t* ei_app_root_widget(void) {
        ei_widget_t *frame_root_widget;
        frame_root_widget->parent = NULL;
        frame_root_widget->requested_size = hw_surface_get_size(root_widget);
        frame_root_widget->screen_location = hw_surface_get_rect(root_widget);
        frame_root_widget->content_rect = &(frame_root_widget->screen_location);
        return frame_root_widget;
}

ei_surface_t ei_app_root_surface(void) {
        return root_widget;
}