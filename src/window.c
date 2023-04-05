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
const int FRAMERATE_LIMIT = 300;

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

                /*
                 * SCALING
                 * */
                // X
                if (event.key.code == sfKeyLeft) {
                    printf("the left key was pressed\n");
                    grid->cube_scaling_axis_factors.x -= 1;
                }
                if (event.key.code == sfKeyRight) {
                    printf("the right key was pressed\n");
                    grid->cube_scaling_axis_factors.x += 1;
                }
                // Y
                if (event.key.code == sfKeyX) {
                    printf("the 'X' key was pressed\n");
                    grid->cube_scaling_axis_factors.y -= 1;
                }
                if (event.key.code == sfKeyC) {
                    printf("the 'C' key was pressed\n");
                    grid->cube_scaling_axis_factors.y += 1;
                }
                // Z
                if (event.key.code == sfKeyDown) {
                    printf("the down key was pressed\n");
                    grid->cube_scaling_axis_factors.z -= 1;
                }
                if (event.key.code == sfKeyUp) {
                    printf("the up key was pressed\n");
                    grid->cube_scaling_axis_factors.z += 1;
                }

                /*
                 * ROTATIONS
                 * */
                if (event.key.code == sfKeyV) {
                    printf("the 'V' key was pressed\n");
                    grid->rotation_axes_deg.x -= 5;
                }
                if (event.key.code == sfKeyB) {
                    printf("the 'B' key was pressed\n");
                    grid->rotation_axes_deg.y -= 5;
                }
                if (event.key.code == sfKeyN) {
                    printf("the 'N' key was pressed\n");
                    grid->rotation_axes_deg.z -= 5;
                }
                if (event.key.code == sfKeyF) {
                    printf("the 'V' key was pressed\n");
                    grid->rotation_axes_deg.x += 5;
                }
                if (event.key.code == sfKeyG) {
                    printf("the 'B' key was pressed\n");
                    grid->rotation_axes_deg.y += 5;
                }
                if (event.key.code == sfKeyH) {
                    printf("the 'N' key was pressed\n");
                    grid->rotation_axes_deg.z += 5;
                }

                /* TRANSLATIONS */
                if (event.key.code == sfKeyA) {
                    printf("the 'A' key was pressed\n");
                    grid->translation_vector.x -= 10;
                }
                if (event.key.code == sfKeyD) {
                    printf("the 'D' key was pressed\n");
                    grid->translation_vector.x += 10;
                }
                if (event.key.code == sfKeyS) {
                    printf("the 'S' key was pressed\n");
                    grid->translation_vector.z -= 10;
                }
                if (event.key.code == sfKeyW) {
                    printf("the 'W' key was pressed\n");
                    grid->translation_vector.z += 10;
                }

                /* PROJECTIONS */
                if (event.key.code == sfKeyEnter) {
                    printf("the 'Enter' key was pressed\n");
                    grid->projector_3d_to_2d = &my_isometric_grid_projection;
                }
                if (event.key.code == sfKeySpace) {
                    printf("the 'Space' key was pressed\n");
                    grid->projector_3d_to_2d = &my_parallel_grid_projection;
                }
            }
        }

        /* Draw here */
        sfColor ground_color = sfCyan;
        ground_color.a /= 4;
        sfColor from_color = sfCyan;
        from_color.a /= 3;
        sfColor to_color = sfCyan;

        //        parallel_projection_test(framebuffer);
        draw_ground(framebuffer, grid, ground_color);
        draw_vertices(framebuffer, grid, from_color, to_color);
        draw_roof(framebuffer, grid, from_color, to_color);
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