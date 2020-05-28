/**
 *  @file	ei_widgettypes.h
 *  @brief	Les différents types de widgetclass
 *
 *  \author Created by Equipe 5 on 13.05.2020.
 */

#ifndef EI_WIDGETTYPES_H
#define EI_WIDGETTYPES_H

#include "SDL_keycode.h"
#include "ei_types.h"
#include "ei_widget.h"

/**
 * @brief	The frame type.
 */
 typedef struct {
     ei_widget_t    widget;

     ei_color_t          color;
     int                 border_width;
     ei_relief_t         relief;
     char*               text;
     ei_font_t           text_font;
     ei_color_t          text_color;
     ei_anchor_t         text_anchor;
     ei_surface_t        img;
     ei_rect_t*          img_rect;
     ei_anchor_t         img_anchor;
 } ei_frame_t;


 /**
  * @brief Structure du type bouton. Un bouton est un frame avec des particulatirés en plus
  */
typedef struct {
    ei_frame_t         frame;

    int			        corner_radius;
    ei_callback_t		callback;
    void*			    user_param;
} ei_button_t;

/**
 * @brief Structure du type toplevel. Un toplevel est un frame avec des particulatirés en plus
 */

typedef struct {
        ei_frame_t         frame;

        ei_frame_t        title_bar;
        ei_button_t*       resize_button;
        ei_button_t*        close_button;

        ei_bool_t          closable;
        ei_axis_set_t      window_resizable;
        ei_size_t*         min_size;
} ei_toplevel_t;


#endif //EI_WIDGETTYPES_H