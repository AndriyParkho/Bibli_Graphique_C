//
// Created by Enora on 15/05/2020.
//

#include "ei_draw.h"
#include <stdlib.h>
#include <stdio.h>
#include "ei_application.h"

/**
 * \brief	Converts the three red, green and blue component of a color in a 32 bits integer
 *		using the order of the channels of the surface. This integer can be stored directly
 *		in the pixels memory of the surface (ie. \ref hw_surface_get_buffer).
 *
 * @param	surface		The surface where to store this pixel.
 * @param	color		The color to convert, can't be NULL.
 *
 * @return 			The 32 bit integer corresponding to the color. The alpha component
 *				of the color is ignored in the case of surfaces that don't have an
 *				alpha channel.
 */
uint32_t		ei_map_rgba		(ei_surface_t surface, const ei_color_t* color){
        int* ir = malloc(sizeof(int));
        int* ig = malloc(sizeof(int));
        int* ib = malloc(sizeof(int));
        int* ia = malloc(sizeof(int));
        uint32_t pixel_val = 0;
        hw_surface_get_channel_indices(surface, ir, ig, ib, ia);

        if(*ia == -1)
                pixel_val = (color->red << 8 * (*ir)) + (color->green << 8 * (*ig)) + (color->blue << 8 * (*ib));
        else
                pixel_val = (color->red << 8 * (*ir)) + (color->green << 8 * (*ig))
                                + (color->blue << 8 * (*ib)) + (color->alpha << 8 * (*ia));
        return pixel_val;
}



/**
 * \brief	Draws a line made of many line segments.
 *
 * @param	surface 	Where to draw the line. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	first_point 	The head of a linked list of the points of the line. It can be NULL
 *				(i.e. draws nothing), can have a single point, or more.
 *				If the last point is the same as the first point, then this pixel is
 *				drawn only once.
 * @param	color		The color used to draw the line, alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void			ei_draw_polyline	(ei_surface_t			surface,
                                     const ei_linked_point_t*	first_point,
                                     const ei_color_t		color,
                                     const ei_rect_t*		clipper);

/**
 * \brief	Draws a filled polygon.
 *
 * @param	surface 	Where to draw the polygon. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	first_point 	The head of a linked list of the points of the line. It is either
 *				NULL (i.e. draws nothing), or has more than 2 points. The last point
 *				is implicitly connected to the first point, i.e. polygons are
 *				closed, it is not necessary to repeat the first point.
 * @param	color		The color used to draw the polygon, alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void			ei_draw_polygon		(ei_surface_t			surface,
                                        const ei_linked_point_t*	first_point,
                                        const ei_color_t		color,
                                        const ei_rect_t*		clipper);

/**
 * \brief	Draws text by calling \ref hw_text_create_surface.
 *
 * @param	surface 	Where to draw the text. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	where		Coordinates, in the surface, where to anchor the top-left corner of
 *				the rendered text.
 * @param	text		The string of the text. Can't be NULL.
 * @param	font		The font used to render the text. If NULL, the \ref ei_default_font
 *				is used.
 * @param	color		The text color. Can't be NULL. The alpha parameter is not used.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void			ei_draw_text		(ei_surface_t		surface,
                                     const ei_point_t*	where,
                                     const char*		text,
                                     const ei_font_t	font,
                                     ei_color_t		color,
                                     const ei_rect_t*	clipper) {
        ei_surface_t surface_du_texte = hw_text_create_surface(text, font, color);
        ei_rect_t* clipperText = (ei_rect_t*)malloc(sizeof(ei_rect_t));
        clipperText->top_left = *where;
        clipperText->size = hw_surface_get_size(surface_du_texte);
        hw_surface_lock(surface_du_texte);
        ei_copy_surface(surface, clipperText, surface_du_texte, NULL, EI_TRUE);
        hw_surface_unlock(surface_du_texte);
        hw_surface_free(surface_du_texte);
}

/**
 * \brief	Fills the surface with the specified color.
 *
 * @param	surface		The surface to be filled. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	color		The color used to fill the surface. If NULL, it means that the
 *				caller want it painted black (opaque).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void ei_fill (ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper) {
        // clipper si non NULL sert à déterminer quel rectangle remplir
        int i;
        ei_size_t surface_size = hw_surface_get_size(surface);

        uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        if (clipper) {
                pixel_ptr = pixel_ptr + surface_size.width * clipper->top_left.y + clipper->top_left.x;
                for (i = 0; i < clipper->size.height * clipper->size.width; i++) {
                        if (i % clipper->size.width == 0 && i != 0) {
                                for (int j = 0; j < (surface_size.width - clipper->size.width); j++) {
                                        pixel_ptr++;
                                }
                        }
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr++;
                }
        } else {
                for (i = 0; i < surface_size.height * surface_size.width; i++) {
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr++;
                }
        }
}

/**
 * \brief	Copies a surface, or a subpart, to another one.
 *		The source and destination area of the copy (either the entire surfaces, or
 *		subparts) must have the same size (before clipping). Both the source and destination
 *		surfaces must be *locked* by \ref hw_surface_lock.
 *
 * @param	destination	The surface on which to copy pixels from the source surface.
 * @param	dst_rect	If NULL, the entire destination surface is used. If not NULL,
 *				defines the rectangle on the destination surface where to copy
 *				the pixels.
 * @param	source		The surface from which to copy pixels.
 * @param	src_rect	If NULL, the entire source surface is used. If not NULL, defines the
 *				rectangle on the source surface from which to copy the pixels.
 * @param	alpha		If true, the final pixels are a combination of source and
 *				destination pixels weighted by the source alpha channel. The
 *				transparency of the final pixels is set	to opaque.
 *				If false, the final pixels are an exact copy of the source pixels,
 				including the alpha channel.
 *
 * @return			Returns 0 on success, 1 on failure (different ROI size).
 */
int			ei_copy_surface		(ei_surface_t		destination,
                                       const ei_rect_t*	dst_rect,
                                       const ei_surface_t	source,
                                       const ei_rect_t*	src_rect,
                                       const ei_bool_t	alpha) {
        // On récupère la taille de nos deux surfaces
        ei_size_t destination_size = hw_surface_get_size(destination);
        ei_size_t source_size = hw_surface_get_size(source);
        // On définit la taille des rectangles dans les quels on utilisera ou changera les pixels
        // Je fais ça pour pas avoir à écrire les boucles for de parcours des pixels dans chaque cas
        ei_size_t src_rect_size;
        ei_size_t dst_rect_size;
        // On fait la même pour le point top_left de ces rectangles
        ei_point_t src_origine;
        ei_point_t dst_origine;
        // On a le cas où les clipper src et dst sont non NULL
        if(dst_rect && src_rect){
                if(dst_rect->size.width != src_rect->size.width || dst_rect->size.height != src_rect->size.height
                   || dst_rect->top_left.x + dst_rect->size.width > destination_size.width
                   || dst_rect->top_left.y + dst_rect->size.height > destination_size.height
                   || src_rect->top_left.x + src_rect->size.width > source_size.width
                   || src_rect->top_left.y + src_rect->size.height > source_size.height)
                        return 1; // S'ils sont de taille différente la fonction fail
                // Ils ont la même taille donc les rectangles qu'on utilisera seront les clippers src et dst
                src_rect_size = src_rect->size;
                dst_rect_size = dst_rect->size;

                src_origine = src_rect->top_left;
                dst_origine = dst_rect->top_left;

        } else if(dst_rect){ // Le cas où src est NULL mais pas dst du coup la src sera la surface entière
                if(dst_rect->size.width != source_size.width || dst_rect->size.height != source_size.height
                   || dst_rect->top_left.x + dst_rect->size.width > destination_size.width
                   || dst_rect->top_left.y + dst_rect->size.height > destination_size.height)
                        return 1;
                // Le rectangle utilisé pour la source sera alors toute la surface source
                src_rect_size = source_size;
                dst_rect_size = dst_rect->size;
                // On fixe l'origine à 0,0 étant donné que c'est la surface qu'on regardera
                src_origine.x = 0;
                src_origine.y = 0;
                dst_origine = dst_rect->top_left;

        } else if (src_rect){ // Pareil ici en inversant src et dst
                if(destination_size.width != src_rect->size.width || destination_size.height != src_rect->size.height
                   || src_rect->top_left.x + src_rect->size.width > source_size.width
                   || src_rect->top_left.y + src_rect->size.height > source_size.height)
                        return 1;

                src_rect_size = src_rect->size;
                dst_rect_size = destination_size;

                src_origine = src_rect->top_left;
                dst_origine.x = 0;
                dst_origine.y = 0;

        } else{
                if(destination_size.width != source_size.width || destination_size.height != source_size.height)
                        return 1;

                src_rect_size = source_size;
                dst_rect_size = destination_size;

                src_origine.x = 0;
                src_origine.y = 0;
                dst_origine.x = 0;
                dst_origine.y = 0;

        }
        int i ;
        uint32_t *pixel_src = (uint32_t *) hw_surface_get_buffer(source);
        uint32_t *pixel_dst = (uint32_t *) hw_surface_get_buffer(destination);
        // On définit les variable qui nous serviront à changer la couleur en prenant en compte la transparence
        uint8_t *red_src;
        uint8_t *red_dst;
        uint8_t *green_src;
        uint8_t *green_dst;
        uint8_t *blue_src;
        uint8_t *blue_dst;
        uint8_t *alpha_src;
        // On récupère l'indice des pixels de la surface source
        int* ir_src = malloc(sizeof(int));
        int* ig_src = malloc(sizeof(int));
        int* ib_src = malloc(sizeof(int));
        int* ia_src = malloc(sizeof(int));
        hw_surface_get_channel_indices(source, ir_src, ig_src, ib_src, ia_src);
        // On récupère l'indice des de la surface destination
        int* ir_dst = malloc(sizeof(int));
        int* ig_dst = malloc(sizeof(int));
        int* ib_dst = malloc(sizeof(int));
        int* ia_dst = malloc(sizeof(int));
        hw_surface_get_channel_indices(destination, ir_dst, ig_dst, ib_dst, ia_dst);
        // On se place au premier pixel des rectangles qu'on utilise
        pixel_src = pixel_src + source_size.width * src_origine.y + src_origine.x;
        pixel_dst = pixel_dst + destination_size.width * dst_origine.y + dst_origine.x;

        for (i = 0; i < src_rect_size.height * src_rect_size.width; i++) {
                if (i % src_rect_size.width == 0 && i != 0) {
                        for (int j = 0; j < (source_size.width - src_rect_size.width); j++) {
                                pixel_src++; // Cette boucle est parcouru que si le rectagle src sur le quel on travail est le clipper src
                        }
                        for (int k = 0; k < (destination_size.width - dst_rect_size.width); k++) {
                                pixel_dst++; // Pareil pour celle-ci avec la dst
                        }
                }
                if(alpha == EI_FALSE)
                        *pixel_dst = *pixel_src;
                else{
                        // Pour chaque couleur on place bien leur pointeur
                        red_src = (uint8_t *)pixel_src + *ir_src;
                        green_src = (uint8_t *)pixel_src + *ig_src;
                        blue_src = (uint8_t *)pixel_src + *ib_src;
                        alpha_src = (uint8_t *)pixel_src + *ia_src;

                        red_dst = (uint8_t *)pixel_dst + *ir_dst;
                        green_dst = (uint8_t *)pixel_dst + *ig_dst;
                        blue_dst = (uint8_t *)pixel_dst + *ib_dst;
                        // On utilise la formule du sujet pour prendre en compte la transparence
                        *red_dst = (*alpha_src * *red_src + (255 - *alpha_src) * *red_dst) / 255;
                        *green_dst = (*alpha_src * *green_src + (255 - *alpha_src) * *green_dst) / 255;
                        *blue_dst = (*alpha_src * *blue_src + (255 - *alpha_src) * *blue_dst) / 255;
                }
                pixel_src++;
                pixel_dst++;
        }
        return 0;
}
