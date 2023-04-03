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
    int loop_count = 0;

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
        /* Clear pixels framebuffer */
        clear_framebuffer(framebuffer);

        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }

            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyDown) {
                    printf("the down key was pressed\n");
                    grid->height_factor -= 0.05;
                }
                if (event.key.code == sfKeyUp) {
                    printf("the up key was pressed\n");
                    grid->height_factor += 0.05;
                }

                // TODO: 3D matrix transformation instead for the size
                if (event.key.code == sfKeyLeft) {
                    printf("the left key was pressed\n");
                    grid->square_size -= 1;
                }
                if (event.key.code == sfKeyRight) {
                    printf("the right key was pressed\n");
                    grid->square_size += 1;
                }
                // TODO: 3D matrix transformation for rotation

                // TODO: move terrain in 3 axes (move start_pos)
                if (event.key.code == sfKeyA) {
                    printf("the 'A' key was pressed\n");
                    grid->pos.x -= 10;
                }
                if (event.key.code == sfKeyD) {
                    printf("the 'D' key was pressed\n");
                    grid->pos.x += 10;
                }
                if (event.key.code == sfKeyS) {
                    printf("the 'S' key was pressed\n");
                    grid->pos.z -= 10;
                }
                if (event.key.code == sfKeyW) {
                    printf("the 'W' key was pressed\n");
                    grid->pos.z += 10;
                }
            }
        }

        /* Draw here */
        //        parallel_projection_test(framebuffer);
        draw_ground(framebuffer, grid, (sfColor){255, 255, 255, 120});
        draw_vertices(framebuffer, grid, sfWhite);
        draw_roof(framebuffer, grid, sfWhite);
        //        my_draw_line(framebuffer, (sfVector2f){500, 500}, (sfVector2f){600, 600}, sfWhite);

        /* Update the texture from the pixels array of the framebuffer */
        sfTexture_updateFromPixels(texture, framebuffer->pixels, framebuffer->width, framebuffer->height, 0, 0);

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
        loop_count += 1;
    }

    /* Cleanup resources */
    framebuffer_destroy(framebuffer);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}