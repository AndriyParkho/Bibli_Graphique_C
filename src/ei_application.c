#include <stdio.h>
#include "ei_widgettypes.h"
#include <stdlib.h>
#include "ei_widgetclass_parcours.h"
#include "ei_widgetclass.h"
#include "ei_widget_frame.h"


ei_surface_t static root_widget;

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
        hw_init();
        root_widget = hw_create_window(main_window_size, fullscreen);
        ei_frame_register_class();
}

void ei_app_free(void) {
        hw_quit();
}

void ei_app_run(void) {
        ei_widget_t *widget; // = ei_app_root_widget(); //jsp
        hw_surface_lock(root_widget);
        widget->wclass->drawfunc(widget, root_widget, root_widget, NULL);
        hw_surface_unlock(root_widget);
        hw_surface_update_rects(root_widget, NULL);

        getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect) {

}

void ei_app_quit_request(void) {

}

ei_widget_t* ei_app_root_widget(void) {
        ei_widget_t *frame_root_widget = malloc(sizeof(ei_widget_t));
        frame_root_widget->wclass = trouve_class(&class_tete, "frame");
        frame_root_widget->parent = NULL;
        frame_root_widget->children_head = NULL;
        frame_root_widget->children_tail = NULL;
        frame_root_widget->next_sibling = NULL;
        frame_root_widget->requested_size = hw_surface_get_size(root_widget);
        frame_root_widget->screen_location = hw_surface_get_rect(root_widget);
        frame_root_widget->content_rect = &(frame_root_widget->screen_location);
        return frame_root_widget;
}

ei_surface_t ei_app_root_surface(void) {
        return root_widget;
}