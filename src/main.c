#include "draw.h"
#include "projections.h"
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

        sfVector2f start_pos = {framebuffer->width / 2 - 200, framebuffer->height / 2};
        sfVector2f end_pos = {framebuffer->width / 2 + 200, framebuffer->height / 2};
        my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

        start_pos.x = framebuffer->width / 2 - 200;
        start_pos.y = framebuffer->height / 2;
        end_pos.x = framebuffer->width / 2 - 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

        start_pos.x = framebuffer->width / 2 + 200;
        start_pos.y = framebuffer->height / 2;
        end_pos.x = framebuffer->width / 2 + 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

        start_pos.x = framebuffer->width / 2 - 200;
        start_pos.y = framebuffer->height / 2 + 200;
        end_pos.x = framebuffer->width / 2 + 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, start_pos, end_pos, sfWhite);


        /*
         * PARALLEL PROJECTION
         * */
        float projection_angle_deg = 30;
        start_pos.x = framebuffer->width / 2 - 200;
        start_pos.y = framebuffer->height / 2;
        end_pos.x = framebuffer->width / 2 + 200;
        end_pos.y = framebuffer->height / 2;
        my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                     my_parallel_projection(end_pos, projection_angle_deg), sfRed);

        start_pos.x = framebuffer->width / 2 - 200;
        start_pos.y = framebuffer->height / 2;
        end_pos.x = framebuffer->width / 2 - 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                     my_parallel_projection(end_pos, projection_angle_deg), sfRed);

        start_pos.x = framebuffer->width / 2 + 200;
        start_pos.y = framebuffer->height / 2;
        end_pos.x = framebuffer->width / 2 + 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                     my_parallel_projection(end_pos, projection_angle_deg), sfRed);

        start_pos.x = framebuffer->width / 2 - 200;
        start_pos.y = framebuffer->height / 2 + 200;
        end_pos.x = framebuffer->width / 2 + 200;
        end_pos.y = framebuffer->height / 2 + 200;
        my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                     my_parallel_projection(end_pos, projection_angle_deg), sfRed);

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
