#include "draw.h"

#ifndef EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
#define EPITECH_WIREFRAME_PROJECT_WIREFRAME_H

struct Grid {
    int **values;
    int rows;
    int cols;
    float parallel_angle_deg;
    float square_size;
    float height_factor;
};

void draw_parallel_ground_line(struct framebuffer *framebuffer, sfVector3f start_pos, sfVector3f end_pos, sfColor color,
                               float angle_degree);
void draw_ground(struct framebuffer *framebuffer, struct Grid *, sfVector3f pos, sfColor color);
void draw_vertices(struct framebuffer *framebuffer, struct Grid *grid, sfVector3f pos, sfColor color);
void draw_roof(struct framebuffer *framebuffer, struct Grid *grid, sfVector3f pos, sfColor color);

#endif//EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
