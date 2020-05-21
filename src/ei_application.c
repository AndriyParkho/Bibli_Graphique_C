#include <stdio.h>
#include "ei_widgettypes.h"
#include <stdlib.h>
#include <ei_geometrytypes.h>
#include "ei_widgetclass_parcours.h"
#include "ei_widgetclass.h"
#include "ei_geometrymanager_parcours.h"


ei_surface_t static root_widget;
static ei_widget_t* frame_root_widget = NULL;

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
        hw_init();
        root_widget = hw_create_window(main_window_size, fullscreen);
        ei_register_placer_manager();
        ei_frame_register_class();
}

void ei_app_free(void) {
        ei_parcours_profondeur_free_widget(frame_root_widget);
        free_class(class_tete);
        free_geometrymanager(geometrymanager_tete);
        hw_quit();
}

void ei_app_run(void) {
        ei_parcours_profondeur_widget(frame_root_widget, root_widget);
        getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect) {

}

void ei_app_quit_request(void) {

}

ei_widget_t* ei_app_root_widget(void) {
        if (frame_root_widget){
                return frame_root_widget;
        }
        ei_widgetclass_t *frame_widgetclass = ei_widgetclass_from_name("frame");
        frame_root_widget = (ei_widget_t*)frame_widgetclass->allocfunc();;
        frame_root_widget->wclass = frame_widgetclass;
        frame_root_widget->wclass->setdefaultsfunc(frame_root_widget);
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