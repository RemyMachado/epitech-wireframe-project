#include "draw.h"

#ifndef EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
#define EPITECH_WIREFRAME_PROJECT_WIREFRAME_H

struct Grid {
    int **values;
    int rows;
    int cols;
};

void draw_ground(struct framebuffer *framebuffer, struct Grid *, sfVector2f pos, int unit_size, sfColor color);

#endif//EPITECH_WIREFRAME_PROJECT_WIREFRAME_H
