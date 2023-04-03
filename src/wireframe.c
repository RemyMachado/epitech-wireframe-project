#include "wireframe.h"
#include "projections.h"
#include "stdio.h"

void draw_parallel_ground_line(struct framebuffer *framebuffer, sfVector2f start_pos, sfVector2f end_pos,
                               sfColor color) {
    int angle_degree = 45;

    my_draw_line(framebuffer, my_parallel_projection(start_pos, angle_degree), my_parallel_projection(end_pos, angle_degree), color);
}

void draw_ground(struct framebuffer *framebuffer, struct Grid *grid, sfVector2f pos, int unit_size, sfColor color) {
    sfVector2f start_pos = {0, 0};
    sfVector2f end_pos = {0, 0};

    // draw a grid with horizontal lines and vertical lines
    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            // top horizontal line
            start_pos.x = pos.x + j * unit_size;
            start_pos.y = pos.y + i * unit_size;
            end_pos.x = pos.x + (j + 1) * unit_size;
            end_pos.y = pos.y + i * unit_size;
            draw_parallel_ground_line(framebuffer, start_pos, end_pos, color);

            // left vertical line
            start_pos.x = pos.x + j * unit_size;
            start_pos.y = pos.y + i * unit_size;
            end_pos.x = pos.x + j * unit_size;
            end_pos.y = pos.y + (i + 1) * unit_size;
            draw_parallel_ground_line(framebuffer, start_pos, end_pos, color);

            // bottom horizontal line
            if (i == grid->rows - 1) {
                start_pos.x = pos.x + j * unit_size;
                start_pos.y = pos.y + (i + 1) * unit_size;
                end_pos.x = pos.x + (j + 1) * unit_size;
                end_pos.y = pos.y + (i + 1) * unit_size;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color);
            }
            // right vertical line
            if (j == grid->cols - 1) {
                start_pos.x = pos.x + (j + 1) * unit_size;
                start_pos.y = pos.y + i * unit_size;
                end_pos.x = pos.x + (j + 1) * unit_size;
                end_pos.y = pos.y + (i + 1) * unit_size;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color);
            }
        }
    }
}
