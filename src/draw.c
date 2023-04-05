#include "draw.h"
#include <SFML/Graphics.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>// for memset

struct framebuffer *framebuffer_create(int width, int height) {
    struct framebuffer *framebuffer = malloc(sizeof(struct framebuffer));

    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->pixels = malloc(sizeof(sfUint8) * 4 * width * height);// 1byte * 4 -> RGBA

    return framebuffer;
}

void clear_framebuffer(struct framebuffer *framebuffer) {
    if (framebuffer && framebuffer->pixels) {
        // Clear pixels to transparent black (0, 0, 0, 0)
        memset(framebuffer->pixels, 0,
               sizeof(sfUint8) * 4 * framebuffer->width * framebuffer->height);// 1byte * 4 -> RGBA
    }
}

void framebuffer_destroy(struct framebuffer *framebuffer) {
    if (framebuffer) {
        if (framebuffer->pixels) {
            free(framebuffer->pixels);
        }
        free(framebuffer);
    }
}

bool is_in_bounds(struct framebuffer *framebuffer, int x, int y) {
    return x >= 0 && x < framebuffer->width && y >= 0 && y < framebuffer->height;
}

void my_put_pixel(struct framebuffer *framebuffer, int x, int y, sfColor color) {
    const int index = (y * framebuffer->width) * 4 + x * 4;

    if (!is_in_bounds(framebuffer, x, y)) return;

    framebuffer->pixels[index] = color.r;
    framebuffer->pixels[index + 1] = color.g;
    framebuffer->pixels[index + 2] = color.b;
    framebuffer->pixels[index + 3] = color.a;
}

void my_put_rect(struct framebuffer *framebuffer, int width, int height, int x, int y, sfColor color) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            my_put_pixel(framebuffer, x + j, y + i, color);
        }
    }
}

void my_draw_square(struct framebuffer *framebuffer, int size, int x, int y, sfColor color) {
    my_put_rect(framebuffer, size, size, x, y, color);
}

void my_put_square_line(struct framebuffer *framebuffer, int size, int quantity, int x, int y, sfColor leftColor,
                        sfColor rightColor) {
    for (int i = 0; i < quantity; ++i) {
        sfUint8 newLeftR = leftColor.r - leftColor.r / quantity * i;
        sfUint8 newLeftG = leftColor.g - leftColor.g / quantity * i;
        sfUint8 newLeftB = leftColor.b - leftColor.b / quantity * i;
        sfUint8 newLeftA = leftColor.a - leftColor.a / quantity * i;

        sfUint8 newRightR = rightColor.r / quantity * i;
        sfUint8 newRightG = rightColor.g / quantity * i;
        sfUint8 newRightB = rightColor.b / quantity * i;
        sfUint8 newRightA = rightColor.a / quantity * i;

        sfColor newColor = {newLeftR + newRightR, newLeftG + newRightG, newLeftB + newRightB, newLeftA + newRightA};

        my_draw_square(framebuffer, size, x + i * size, y, newColor);
    }
}

void my_put_square_matrix(struct framebuffer *framebuffer, int squareSize, int matrixSize, int x, int y,
                          sfColor topLeftColor, sfColor topRightColor, sfColor bottomRightColor,
                          sfColor bottomLeftColor) {
    for (int i = 0; i < matrixSize; ++i) {
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

// TODO: isometric projection

/*
 * Array terminated by sentinel point (FLT_MAX, FLT_MAX)
 * */
sfVector2f *get_line_points(sfVector2f from, sfVector2f to) {
    sfVector2f *points = NULL;
    float slope = 0;
    float b = from.y;
    sfVector2f vector = {to.x - from.x, to.y - from.y};

    // vertical line
    if (vector.x == 0) {
        points = malloc(sizeof(sfVector2f) * (fabs(vector.y) + 1));// +1 for terminator

        if (vector.y > 0) {
            for (int y = 0; y < vector.y; ++y) {
                points[y] = (sfVector2f){from.x, b + y};
            }
        } else {

            for (int y = 0; y > vector.y; --y) {
                points[abs(y)] = (sfVector2f){from.x, b + y};
            }
        }
        points[(int) fabs(vector.y)] = (sfVector2f){FLT_MAX, FLT_MAX};

        return points;
    }

    slope = vector.y / vector.x;

    // if `y` is growing faster than `x`, then we have to draw on the y-axis for a nicer axis drawing
    if (fabs(slope) > 1) {
        points = malloc(sizeof(sfVector2f) * (fabs(vector.y) + 1));// +1 for terminator

        if (vector.y > 0) {
            for (int y = 0; y < vector.y; ++y) {
                const float x = y / slope;

                points[y] = (sfVector2f){from.x + x, b + y};
            }
        } else {
            for (int y = 0; y > vector.y; --y) {
                const float x = y / slope;

                points[abs(y)] = (sfVector2f){from.x + x, b + y};
            }
        }
        points[(int) fabs(vector.y)] = (sfVector2f){FLT_MAX, FLT_MAX};
    } else {
        points = malloc(sizeof(sfVector2f) * (fabs(vector.x) + 1));// +1 for terminator

        if (vector.x > 0) {
            for (int x = 0; x < vector.x; ++x) {
                /* y = ax + b */
                const float y = slope * x + b;

                points[x] = (sfVector2f){from.x + x, y};
            }
        } else {
            for (int x = 0; x > vector.x; --x) {
                /* y = ax + b */
                const float y = slope * x + b;

                points[abs(x)] = (sfVector2f){from.x + x, y};
            }
        }

        points[(int) fabs(vector.x)] = (sfVector2f){FLT_MAX, FLT_MAX};
    }

    return points;
}

int length_of_points(sfVector2f *points) {
    int size = 0;

    for (int i = 0; points[i].x != FLT_MAX; ++i) {
        ++size;
    }

    return size;
}

void my_draw_line_gradient(struct framebuffer *framebuffer, sfVector2f from_pos, sfVector2f to_pos, sfColor from_color,
                           sfColor to_color) {
    sfVector2f *points = get_line_points(from_pos, to_pos);
    int points_length = length_of_points(points);

    for (int i = 0; i < points_length; ++i) {
        float color_percentage = (float) i / (float) points_length;

        sfColor color = {from_color.r + (to_color.r - from_color.r) * color_percentage,
                         from_color.g + (to_color.g - from_color.g) * color_percentage,
                         from_color.b + (to_color.b - from_color.b) * color_percentage,
                         from_color.a + (to_color.a - from_color.a) * color_percentage};

        my_put_pixel(framebuffer, points[i].x, points[i].y, color);
    }

    free(points);
}

/* y = ax + b */
void my_draw_line(struct framebuffer *framebuffer, sfVector2f from, sfVector2f to, sfColor color) {
    float slope = 0;
    float b = from.y;
    sfVector2f vector = {to.x - from.x, to.y - from.y};

    // vertical line
    if (vector.x == 0) {
        if (vector.y > 0) {
            for (int y = 0; y < vector.y; ++y) {
                my_put_pixel(framebuffer, from.x, b + y, color);
            }
        } else {
            for (int y = 0; y > vector.y; --y) {
                my_put_pixel(framebuffer, from.x, b + y, color);
            }
        }

        return;
    }

    slope = vector.y / vector.x;

    // if `y` is growing faster than `x`, then we have to draw on the y-axis for a nicer axis drawing
    if (fabs(slope) > 1) {
        if (vector.y > 0) {
            for (int y = 0; y < vector.y; ++y) {
                const float x = y / slope;

                my_put_pixel(framebuffer, from.x + x, b + y, color);
            }
        } else {
            for (int y = 0; y > vector.y; --y) {
                const float x = y / slope;

                my_put_pixel(framebuffer, from.x + x, b + y, color);
            }
        }
    } else {
        if (vector.x > 0) {
            for (int x = 0; x < vector.x; ++x) {
                /* y = ax + b */
                const float y = slope * x + b;

                my_put_pixel(framebuffer, from.x + x, y, color);
            }
        } else {
            for (int x = 0; x > vector.x; --x) {
                /* y = ax + b */
                const float y = slope * x + b;

                my_put_pixel(framebuffer, from.x + x, y, color);
            }
        }
    }
}
