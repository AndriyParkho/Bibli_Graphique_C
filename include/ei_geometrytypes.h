/**
 *  @file	ei_geometrytypes.h
 *  @brief	Les différentes structures de geometrymanager_param
 *
 *  \author Created by Equipe 5 on 18.05.2020.
 */

#ifndef EI_GEOMETRYTYPES_H
#define EI_GEOMETRYTYPES_H

#include "SDL_keycode.h"
#include "ei_types.h"
#include "ei_geometrymanager.h"

typedef struct {
    ei_geometrymanager_t* manager;


    ei_anchor_t anchor;
    int         x;
    int         y;
    int         width;
    int         height;
    float       rel_x;
    float       rel_y;
    float       rel_width;
    float       rel_height;
} ei_placer_param_t;

#endif
