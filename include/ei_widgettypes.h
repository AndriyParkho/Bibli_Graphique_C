//
// Created by Enora on 13/05/2020.
//

#ifndef EI_WIDGETTYPES_H
#define EI_WIDGETTYPES_H

#include "SDL_keycode.h"
#include "ei_types.h"

/**
 * @brief	The frame type.
 */
 typedef struct {
     ei_widget_t    widget;

     ei_relief_t         relief;
     char*               text;
     ei_font_t           text_font;
     ei_color_t          text_color;
     ei_anchor_t         text_anchor;
     ei_surface_t*       img;
     ei_rect_t*          img_rect;
     ei_anchor_t*        img_anchor;
 } ei_frame_t;


#endif //PROJETC_IG_EI_WIDGETTYPES_H