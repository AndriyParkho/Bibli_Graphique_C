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

/*        if (*ir == 0 || *ir == 1){ // De la forme ARGB ou RGBA
                pixel_val = color->blue;
                pixel_val = (color->green << 8) + pixel_val;
                pixel_val = (color->red << 16) + pixel_val;
        } else { // De la forme ABGR ou BGRA
                pixel_val = color->red;
                pixel_val = (color->green << 8) + pixel_val;
                pixel_val = (color->blue << 16) + pixel_val;
        }

        if (*ir + *ig + *ib == 6) { // De la forme AXXX
                pixel_val = (color->alpha << 24) + pixel_val;
        } else { // De la forme XXXA
                pixel_val = color->alpha + (pixel_val << 8);
        }*/
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
        hw_surface_lock(surface);
        ei_fill(surface_du_texte, &color, clipper);
        hw_surface_unlock(surface);
        hw_surface_update_rects(surface, NULL);
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
        ei_size_t root_size = hw_surface_get_size(ei_app_root_surface());
        if (clipper) {
                surface_size = clipper->size;
        }
        pixel_ptr = pixel_ptr + root_size.width*clipper->top_left.y + clipper->top_left.x;
        for (i = 0; i < surface_size.height * surface_size.width; i++) {
                if (i%surface_size.width == 0 && i!=0) {
                        for (int j=0; j<(root_size.width-surface_size.width); j++) {
                                pixel_ptr++;
                        }
                }
                *pixel_ptr = ei_map_rgba(surface, color);
                pixel_ptr++;
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
                                       const ei_bool_t	alpha);
