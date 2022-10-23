#include <SFML/Graphics.h>

#ifndef EPITECH_WIREFRAME_PROJECT_DRAW_H
#define EPITECH_WIREFRAME_PROJECT_DRAW_H

struct framebuffer {
    unsigned int width;
    unsigned int height;
    sfUint8 *pixels;
};

struct framebuffer *framebuffer_create(unsigned int width, unsigned int height);
void framebuffer_destroy(struct framebuffer *framebuffer);

void my_put_pixel(struct framebuffer *framebuffer, unsigned int x, unsigned int y, sfColor color);
void my_put_rect(struct framebuffer *framebuffer, unsigned int width, unsigned int height, unsigned int x,
                 unsigned int y, sfColor color);
void my_put_square(struct framebuffer *framebuffer, unsigned int size, unsigned int x, unsigned int y, sfColor color);
void my_put_square_line(struct framebuffer *framebuffer, unsigned int size, unsigned int quantity, unsigned int x,
                        unsigned int y, sfColor leftColor, sfColor rightColor);
void my_put_square_matrix(struct framebuffer *framebuffer, unsigned int squareSize, unsigned int matrixSize,
                          unsigned int x, unsigned int y, sfColor topLeftColor, sfColor topRightColor,
                          sfColor bottomRightColor, sfColor bottomLeftColor);

#endif//EPITECH_WIREFRAME_PROJECT_DRAW_H
