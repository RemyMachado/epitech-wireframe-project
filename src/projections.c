#include "projections.h"
#include "math.h"

// converts a 3D point to a 2D point using the parallel projection
// (angle is in degree):
// TODO: try with matrix transformation

/*
 *
 * Transformation matrix:
 * [1][cos(A)][0]
 * [0][  1   ][0]
 * [0][  0   ][1]
 * */
sfVector2f my_parallel_projection(sfVector2f pos2d, float angle_deg) {
    float angle_rad = M_PI / 180 * (angle_deg + 90);
    float new_x = pos2d.x + pos2d.y * cos(angle_rad);
    float new_y = pos2d.y;

    sfVector2f new_pos2f = {new_x, new_y};

    return new_pos2f;
}
