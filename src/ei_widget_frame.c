/*
 *  Fichier où il y aura toutes les fonctions des différents widgets
 */

void frame_draw(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;

}


void ei_frame_allocfunc(){
        return(calloc(sizeof(ei_frame_t)));
}


void ei_frame_releasefunc(ei_frame_t* frame){
        free(frame);
}


void ei_frame_setdefaultsfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}


void ei_frame_geomnotifyfunc(ei_widget_t* widget){
        ei_frame_t* frame = (ei_frame_t*)widget;
}