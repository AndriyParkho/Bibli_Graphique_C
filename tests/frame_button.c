#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"


/*
 * button_press --
 *
 *	Callback called when a user clicks on the button.
 */
ei_bool_t button_press(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
        printf("Click !\n");
        return EI_TRUE;
}

/*
 * process_key --
 *
 *	Callback called when any key is pressed by the user.
 *	Simply looks for the "Escape" key to request the application to quit.
 */
ei_bool_t process_key(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
        if (event->param.key.key_code == SDLK_ESCAPE) {
                ei_app_quit_request();
                return EI_TRUE;
        }

        return EI_FALSE;
}

ei_bool_t coucou(ei_widget_t* widget, ei_event_t* event, void* user_param)
{
        if (event->param.key.key_code == SDLK_ESCAPE) {
                printf("Coucou\n");
                return EI_TRUE;
        }

        return EI_FALSE;
}

/*
 * main --
 *
 *	Main function of the application.
 */
int main(int argc, char** argv)
{
        ei_size_t	screen_size		= {600, 600};
        ei_color_t	root_bgcol		= {0x52, 0x7f, 0xb4, 0xff};

        ei_widget_t*    frame;
        ei_size_t       frame_size              = {400, 400};
        int             frame_x                 = 100;
        int             frame_y                 = 100;
        ei_color_t      frame_color             = {0x00, 0x00, 0xff, 0xff};
        ei_relief_t     frame_relief            = ei_relief_raised;
        int             frame_border_width      = 5;

        ei_widget_t*	button;
        ei_size_t	button_size		= {200,100};
        ei_anchor_t     button_anchor           = ei_anc_southeast;
        float           button_rel_x            = 1.0;
        float           button_rel_y            = 1.0;
        int		button_x		= -10;
        int		button_y		= -10;
        ei_color_t	button_color		= {0xff, 0x00, 0x00, 0xff};
        char*		button_title		= "Rouge";
        ei_color_t	button_text_color	= {0x00, 0x00, 0x00, 0xff};
        int		button_corner_radius	= 20;
        ei_relief_t	button_relief		= ei_relief_sunken;
        int		button_border_width	= 6;
        ei_callback_t	button_callback 	= button_press;

        /* Create the application and change the color of the background. */
        ei_app_create(screen_size, EI_FALSE);
        ei_frame_configure(ei_app_root_widget(), NULL, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        /* Create configure and place the frame on screen*/
        frame = ei_widget_create("frame", ei_app_root_widget(), NULL, NULL);
        ei_frame_configure(frame, &frame_size, &frame_color,
                           &frame_border_width, &frame_relief, NULL, NULL, NULL, NULL,
                           NULL, NULL, NULL);
        ei_place(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL );


        /* Create, configure and place the button on screen. */
        button = ei_widget_create("button", frame, NULL, NULL);
        ei_button_configure	(button, &button_size, &button_color,
                                    &button_border_width, &button_corner_radius, &button_relief, &button_title, NULL, &button_text_color, NULL,
                                    NULL, NULL, NULL, &button_callback, NULL);
        ei_place(button, &button_anchor, &button_x, &button_y, NULL, NULL, &button_rel_x, &button_rel_y, NULL, NULL );

        /* Hook the keypress callback to the event. */
        ei_bind(ei_ev_keydown,		NULL, "all", process_key, NULL);

        /* Run the application's main loop. */
        ei_app_run();

        /* We just exited from the main loop. Terminate the application (cleanup). */
        //ei_unbind(ei_ev_keydown,	NULL, "all", process_key, NULL);
        ei_app_free();

        return (EXIT_SUCCESS);
}