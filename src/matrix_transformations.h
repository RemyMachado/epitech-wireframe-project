#ifndef EPITECH_WIREFRAME_PROJECT_MATRIX_TRANSFORMATIONS_H
#define EPITECH_WIREFRAME_PROJECT_MATRIX_TRANSFORMATIONS_H

#include "draw.h"

sfVector3f apply_transformation_3d(sfVector3f initial_vector, sfVector3f new_unit_x, sfVector3f new_unit_y,
                                   sfVector3f new_unit_z);
sfVector3f apply_scaling_3d(sfVector3f initial_vector, sfVector3f scaling_axis_factors);
sfVector3f apply_rotation_3d_deg(sfVector3f initial_vector, sfVector3f rotation_axes_deg);
sfVector3f apply_translation_3d(sfVector3f initial_vector, sfVector3f translation_vector);

#endif//EPITECH_WIREFRAME_PROJECT_MATRIX_TRANSFORMATIONS_H
