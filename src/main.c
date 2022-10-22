#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

const char *WINDOW_TITLE = "Epitech-Wireframe";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const unsigned int WINDOW_BITS_PER_PIXEL = 32;
const unsigned int FRAMERATE_LIMIT = 300;// TODO: 30

struct framebuffer {
    unsigned int width;
    unsigned int height;
    sfUint8 *pixels;
};

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

void my_put_pixel(struct framebuffer *framebuffer, unsigned int x, unsigned int y, sfColor color) {
    const int index = (y * framebuffer->width) * 4 + x * 4;

    framebuffer->pixels[index] = color.r;
    framebuffer->pixels[index + 1] = color.g;
    framebuffer->pixels[index + 2] = color.b;
    framebuffer->pixels[index + 3] = color.a;
}

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

    printf("Hello, World!\n");

    int i = 0;
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_display(window);

        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) { sfRenderWindow_close(window); }
        }

        /* Draw the pixel at (100,100) in the framebuffer */
        my_put_pixel(framebuffer, i, 0, sfRed);

        /* Update the texture from the pixels array of the framebuffer */
        sfTexture_updateFromPixels(texture, framebuffer->pixels, framebuffer->width, framebuffer->height, 0, 0);

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
        if (i < 1920) { ++i; }
    }

    /* Cleanup resources */
    framebuffer_destroy(framebuffer);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
