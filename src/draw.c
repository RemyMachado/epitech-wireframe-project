#include "draw.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

struct framebuffer *framebuffer_create(unsigned int width, unsigned int height) {
    struct framebuffer *framebuffer = malloc(sizeof(struct framebuffer));

    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->pixels = malloc(sizeof(sfUint8) * 4 * width * height);// 1byte * 4 -> RGBA

    return framebuffer;
}

void framebuffer_destroy(struct framebuffer *framebuffer) {
    free(framebuffer);
}

// TODO: consider adding a guard to prevent x,y overflow
void my_put_pixel(struct framebuffer *framebuffer, unsigned int x, unsigned int y, sfColor color) {
    const int index = (y * framebuffer->width) * 4 + x * 4;

    framebuffer->pixels[index] = color.r;
    framebuffer->pixels[index + 1] = color.g;
    framebuffer->pixels[index + 2] = color.b;
    framebuffer->pixels[index + 3] = color.a;
}

void my_put_rect(struct framebuffer *framebuffer, unsigned int width, unsigned int height, unsigned int x,
                 unsigned int y, sfColor color) {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            my_put_pixel(framebuffer, x + j, y + i, color);
        }
    }
}

void my_put_square(struct framebuffer *framebuffer, unsigned int size, unsigned int x, unsigned int y, sfColor color) {
    my_put_rect(framebuffer, size, size, x, y, color);
}

void my_put_square_line(struct framebuffer *framebuffer, unsigned int size, unsigned int quantity, unsigned int x,
                        unsigned int y, sfColor leftColor, sfColor rightColor) {
    for (unsigned int i = 0; i < quantity; ++i) {
        sfUint8 newLeftR = leftColor.r - leftColor.r / quantity * i;
        sfUint8 newLeftG = leftColor.g - leftColor.g / quantity * i;
        sfUint8 newLeftB = leftColor.b - leftColor.b / quantity * i;
        sfUint8 newLeftA = leftColor.a - leftColor.a / quantity * i;

        sfUint8 newRightR = rightColor.r / quantity * i;
        sfUint8 newRightG = rightColor.g / quantity * i;
        sfUint8 newRightB = rightColor.b / quantity * i;
        sfUint8 newRightA = rightColor.a / quantity * i;

        sfColor newColor = {newLeftR + newRightR, newLeftG + newRightG, newLeftB + newRightB, newLeftA + newRightA};

        my_put_square(framebuffer, size, x + i * size, y, newColor);
    }
}

void my_put_square_matrix(struct framebuffer *framebuffer, unsigned int squareSize, unsigned int matrixSize,
                          unsigned int x, unsigned int y, sfColor topLeftColor, sfColor topRightColor,
                          sfColor bottomRightColor, sfColor bottomLeftColor) {
    for (unsigned int i = 0; i < matrixSize; ++i) {
        sfUint8 newTopLeftR = topLeftColor.r - topLeftColor.r / matrixSize * i;
        sfUint8 newTopLeftG = topLeftColor.g - topLeftColor.g / matrixSize * i;
        sfUint8 newTopLeftB = topLeftColor.b - topLeftColor.b / matrixSize * i;
        sfUint8 newTopLeftA = topLeftColor.a - topLeftColor.a / matrixSize * i;

        sfUint8 newBottomLeftR = bottomLeftColor.r / matrixSize * i;
        sfUint8 newBottomLeftG = bottomLeftColor.g / matrixSize * i;
        sfUint8 newBottomLeftB = bottomLeftColor.b / matrixSize * i;
        sfUint8 newBottomLeftA = bottomLeftColor.a / matrixSize * i;

        sfUint8 newTopRightR = topRightColor.r - topRightColor.r / matrixSize * i;
        sfUint8 newTopRightG = topRightColor.g - topRightColor.g / matrixSize * i;
        sfUint8 newTopRightB = topRightColor.b - topRightColor.b / matrixSize * i;
        sfUint8 newTopRightA = topRightColor.a - topRightColor.a / matrixSize * i;

        sfUint8 newBottomRightR = bottomRightColor.r / matrixSize * i;
        sfUint8 newBottomRightG = bottomRightColor.g / matrixSize * i;
        sfUint8 newBottomRightB = bottomRightColor.b / matrixSize * i;
        sfUint8 newBottomRightA = bottomRightColor.a / matrixSize * i;

        sfColor newLeftColor = {newTopLeftR + newBottomLeftR, newTopLeftG + newBottomLeftG,
                                newTopLeftB + newBottomLeftB, newTopLeftA + newBottomLeftA};

        sfColor newRightColor = {newTopRightR + newBottomRightR, newTopRightG + newBottomRightG,
                                 newTopRightB + newBottomRightB, newTopRightA + newBottomRightA};

        my_put_square_line(framebuffer, squareSize, matrixSize, x, y + (squareSize * i), newLeftColor, newRightColor);
    }
}
