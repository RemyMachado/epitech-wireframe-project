#include "matrix_transformations.h"
#include "my_math.h"
#include <math.h>

sfVector3f apply_transformation_3d(sfVector3f initial_vector, sfVector3f new_unit_x, sfVector3f new_unit_y,
                                   sfVector3f new_unit_z) {
    sfVector3f new_vector = {0, 0, 0};

    new_vector.x = initial_vector.x * new_unit_x.x + initial_vector.y * new_unit_y.x + initial_vector.z * new_unit_z.x;
    new_vector.y = initial_vector.x * new_unit_x.y + initial_vector.y * new_unit_y.y + initial_vector.z * new_unit_z.y;
    new_vector.z = initial_vector.x * new_unit_x.z + initial_vector.y * new_unit_y.z + initial_vector.z * new_unit_z.z;

    return new_vector;
}

sfVector3f apply_scaling_3d(sfVector3f initial_vector, sfVector3f scaling_axis_factors) {
    sfVector3f new_vector = {0, 0, 0};

    new_vector.x = initial_vector.x * scaling_axis_factors.x;
    new_vector.y = initial_vector.y * scaling_axis_factors.y;
    new_vector.z = initial_vector.z * scaling_axis_factors.z;

    return new_vector;
}

/*
 * Rotation order is X, Y, Z
 * Coordinate system: left-handed Z-up
 * */
sfVector3f apply_rotation_3d_deg(sfVector3f initial_vector, sfVector3f rotation_axes_deg) {
    float rotation_x_rad = degrees_to_radians(rotation_axes_deg.x);
    float rotation_y_rad = degrees_to_radians(rotation_axes_deg.y);
    float rotation_z_rad = degrees_to_radians(rotation_axes_deg.z);

    // Rotation around X axis
    sfVector3f rotation_x_new_unit_x = {1, 0, 0};
    sfVector3f rotation_x_new_unit_y = {0, cosf(rotation_x_rad), -1 * sinf(rotation_x_rad)};
    sfVector3f rotation_x_new_unit_z = {0, sinf(rotation_x_rad), cosf(rotation_x_rad)};

    sfVector3f vector_after_x_rotation = apply_transformation_3d(initial_vector, rotation_x_new_unit_x,
                                                                 rotation_x_new_unit_y, rotation_x_new_unit_z);

    // Rotation around Y axis
    sfVector3f rotation_y_new_unit_x = {cosf(rotation_y_rad), 0, sinf(rotation_y_rad)};
    sfVector3f rotation_y_new_unit_y = {0, 1, 0};
    sfVector3f rotation_y_new_unit_z = {-1 * sinf(rotation_y_rad), 0, cosf(rotation_y_rad)};

    sfVector3f vector_after_y_rotation = apply_transformation_3d(vector_after_x_rotation, rotation_y_new_unit_x,
                                                                 rotation_y_new_unit_y, rotation_y_new_unit_z);

    // Rotation around Z axis
    sfVector3f rotation_z_new_unit_x = {cosf(rotation_z_rad), -1 * sinf(rotation_z_rad), 0};
    sfVector3f rotation_z_new_unit_y = {sinf(rotation_z_rad), cosf(rotation_z_rad), 0};
    sfVector3f rotation_z_new_unit_z = {0, 0, 1};

    sfVector3f vector_after_z_rotation = apply_transformation_3d(vector_after_y_rotation, rotation_z_new_unit_x,
                                                                 rotation_z_new_unit_y, rotation_z_new_unit_z);

    return vector_after_z_rotation;
}

sfVector3f apply_translation_3d(sfVector3f initial_vector, sfVector3f translation_vector) {
    sfVector3f new_vector = {0, 0, 0};

    new_vector.x = initial_vector.x + translation_vector.x;
    new_vector.y = initial_vector.y + translation_vector.y;
    new_vector.z = initial_vector.z + translation_vector.z;

    return new_vector;
}
