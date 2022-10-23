#include "draw.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NOMINMAX

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#endif /* NOMINMAX */

const char *WINDOW_TITLE = "Epitech-Wireframe";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const unsigned int WINDOW_BITS_PER_PIXEL = 32;
const unsigned int FRAMERATE_LIMIT = 300;// TODO: 30

int main() {
    sfVideoMode videoMode = {WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BITS_PER_PIXEL};
    sfRenderWindow *window;
    struct framebuffer *framebuffer;
    sfTexture *texture;
    sfSprite *sprite;
    sfEvent event;

    window = sfRenderWindow_create(videoMode, WINDOW_TITLE, sfClose | sfResize, NULL);
    if (!window) return EXIT_FAILURE;

    /* Create the framebuffer */
    framebuffer = framebuffer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Load a sprite to display (including its texture) */
    texture = sfTexture_create(framebuffer->width, framebuffer->height);
    if (!texture) return EXIT_FAILURE;

    sprite = sfSprite_create();

    /* Link the texture to the sprite */
    sfSprite_setTexture(sprite, texture, sfTrue);

    /* Limit the window framerate */
    sfRenderWindow_setFramerateLimit(window, FRAMERATE_LIMIT);

    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_display(window);

        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        /* Draw the pixel at (100,100) in the framebuffer */
        //        my_put_pixel(framebuffer, 100, 100, sfRed);
        //        my_put_square(framebuffer, 300, 500, 200, sfRed);
        //        my_put_square_line(framebuffer, 150, 10, 0, 0, sfRed, sfBlue);
        //        my_put_square_matrix(framebuffer, 90, 10, 0, 0, sfRed, sfBlue, sfCyan, sfYellow);
        //        my_put_square_matrix(framebuffer, 18, 50, 0, 0, sfRed, sfBlue, sfCyan, sfYellow);
        //        my_put_square_matrix(framebuffer, 9, 100, 0, 0, sfRed, sfBlue, sfCyan, sfYellow);
        my_put_rect(framebuffer, framebuffer->width / 2, framebuffer->height / 2, 0, 0, sfBlue);
        my_put_rect(framebuffer, framebuffer->width / 2, framebuffer->height / 2, framebuffer->width / 2, 0, sfRed);
        my_put_rect(framebuffer, framebuffer->width / 2, framebuffer->height / 2, 0, framebuffer->height / 2, sfGreen);
        my_put_rect(framebuffer, framebuffer->width / 2, framebuffer->height / 2, framebuffer->width / 2,
                    framebuffer->height / 2, sfCyan);
        my_draw_line(framebuffer, (sfVector2f){framebuffer->width / 2 + 200, framebuffer->height / 2 - 200},
                     (sfVector2f){framebuffer->width / 2 - 200, framebuffer->height / 2 + 200}, sfWhite);

        /* Update the texture from the pixels array of the framebuffer */
        sfTexture_updateFromPixels(texture, framebuffer->pixels, framebuffer->width, framebuffer->height, 0, 0);

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    framebuffer_destroy(framebuffer);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
