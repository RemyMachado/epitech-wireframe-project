#include "draw.h"
#include <SFML/Graphics.h>

#ifndef EPITECH_WIREFRAME_PROJECT_PROJECTIONS_H
#define EPITECH_WIREFRAME_PROJECT_PROJECTIONS_H

sfVector2f my_parallel_projection(sfVector2f pos2d, float angle);
void parallel_projection_test(struct framebuffer *framebuffer);

sfVector2f my_isometric_projection(sfVector2f pos2d);
void isometric_projection_test(struct framebuffer *framebuffer);

#endif//EPITECH_WIREFRAME_PROJECT_PROJECTIONS_H
