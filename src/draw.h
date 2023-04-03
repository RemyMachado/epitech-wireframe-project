#include <SFML/Graphics.h>
#include <stdbool.h>

#ifndef EPITECH_WIREFRAME_PROJECT_DRAW_H
#define EPITECH_WIREFRAME_PROJECT_DRAW_H

struct framebuffer {
    int width;
    int height;
    sfUint8 *pixels;
};

struct framebuffer *framebuffer_create(int width, int height);
void clear_framebuffer(struct framebuffer *framebuffer);
void framebuffer_destroy(struct framebuffer *framebuffer);
bool is_in_bounds(struct framebuffer *framebuffer, int x, int y);

void my_put_pixel(struct framebuffer *framebuffer, int x, int y, sfColor color);
void my_put_rect(struct framebuffer *framebuffer, int width, int height, int x, int y, sfColor color);
void my_draw_square(struct framebuffer *framebuffer, int size, int x, int y, sfColor color);
void my_put_square_line(struct framebuffer *framebuffer, int size, int quantity, int x, int y, sfColor leftColor,
                        sfColor rightColor);
void my_put_square_matrix(struct framebuffer *framebuffer, int squareSize, int matrixSize, int x, int y,
                          sfColor topLeftColor, sfColor topRightColor, sfColor bottomRightColor,
                          sfColor bottomLeftColor);

void my_draw_line(struct framebuffer *framebuffer, sfVector2f from, sfVector2f to, sfColor color);

#endif//EPITECH_WIREFRAME_PROJECT_DRAW_H
