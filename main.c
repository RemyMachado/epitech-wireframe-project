#include <stdio.h>
#include <SFML/Graphics.h>

int main() {
    sfRenderWindow *window;
    sfVideoMode videoMode = {1920, 1080, 32};
    sfEvent event;

    printf("Hello, World!\n");
    window = sfRenderWindow_create(videoMode, "Epitech-Wireframe", sfClose, NULL);

    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_display(window);

        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }
    }

    return 0;
}
