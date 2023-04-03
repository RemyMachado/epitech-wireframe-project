#include "window.h"
#include "draw.h"
#include "projections.h"
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

const char *WINDOW_TITLE = "Epitech-Wireframe";
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int WINDOW_BITS_PER_PIXEL = 32;
const int FRAMERATE_LIMIT = 300;// TODO: 30

int run_window_loop(struct Grid *grid) {
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

        /* Draw here */
        //        parallel_projection_test(framebuffer);
        sfVector3f start_pos = {800, 500, 0};

        draw_ground(framebuffer, grid, start_pos, (sfColor){255, 255, 255, 120});
        draw_vertices(framebuffer, grid, start_pos, sfWhite);
        draw_roof(framebuffer, grid, start_pos, sfWhite);
        //        my_draw_line(framebuffer, (sfVector2f){500, 500}, (sfVector2f){600, 600}, sfWhite);

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