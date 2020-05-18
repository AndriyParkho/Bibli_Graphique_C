/*
 * Fonctions propre au manager placer
 */


#include "ei_geometrymanager_placer.h"
#include "ei_geometrytypes.h"
#include <string.h>

/**
 * \brief	A function that runs the geometry computation for this widget. This may trigger
 *		geometry computation for this widget's parent and the other children of the parent, pour un
 *		geometrymanager de type placer
 *
 * @param	widget		The widget instance for which to compute geometry.
 */
void placer_runfunc(ei_widget_t* widget){

}

/**
 * \brief	A function called when a widget cease to be managed by its geometry manager.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets, pour un geometrymanager de type placer
 *
 * @param	widget		The widget instance that must be forgotten by the geometry manager.
 */
void placer_releasefunc(ei_widget_t* widget){

}

/**
 * \brief Fonction permettant de rajouter un geometrymanager de type placer dans la liste des geometrymanager
 */
void ei_placer_register() {
    ei_geometrymanager_t *placer = (ei_geometrymanager_t *)malloc(sizeof(ei_geometrymanager_t*));
    strcpy(placer->name, "placer");
    placer->runfunc = &placer_runfunc;
    placer->releasefunc = &placer_releasefunc;
    placer->next = NULL;
    ei_geometrymanager_register(placer);
}