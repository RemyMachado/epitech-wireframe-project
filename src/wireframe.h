#include "draw.h"

#ifndef EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
#define EPITECH_WIREFRAME_PROJECT_WIREFRAME_H

struct Grid {
    int **values;
    int rows;
    int cols;
    int max_value;
    sfVector3f pos;
    float parallel_angle_deg;
    float isometric_angle_deg;
    sfVector3f cube_scaling_axis_factors;
    sfVector3f rotation_axes_deg;
    sfVector3f translation_vector;
    sfVector2f (*projector_3d_to_2d)(struct Grid *, sfVector3f);
};

void draw_parallel_ground_line(struct framebuffer *framebuffer, struct Grid *grid, sfVector3f start_pos,
                               sfVector3f end_pos, sfColor color);
void draw_ground(struct framebuffer *framebuffer, struct Grid *, sfColor color);
void draw_vertices(struct framebuffer *framebuffer, struct Grid *grid, sfColor from_color, sfColor to_color);
void draw_roof(struct framebuffer *framebuffer, struct Grid *grid, sfColor from_color, sfColor to_color);

sfVector2f my_parallel_grid_projection(struct Grid *grid, sfVector3f pos3d);
sfVector2f my_isometric_grid_projection(struct Grid *grid, sfVector3f pos3d);

#endif//EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
