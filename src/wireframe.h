#include "draw.h"

#ifndef EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
#define EPITECH_WIREFRAME_PROJECT_WIREFRAME_H

struct Grid {
    int **values;
    int rows;
    int cols;
};

void draw_ground(struct framebuffer *framebuffer, struct Grid *, sfVector3f pos, int unit_size, sfColor color);
void draw_vertices(struct framebuffer *framebuffer, struct Grid *grid, sfVector3f pos, int unit_size, sfColor color);

#endif//EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
