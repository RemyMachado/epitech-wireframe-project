#include "wireframe.h"
#include "projections.h"

void draw_parallel_ground_line(struct framebuffer *framebuffer, sfVector3f start_pos, sfVector3f end_pos, sfColor color,
                               float angle_degree) {
    my_draw_line(framebuffer, my_parallel_projection(start_pos, angle_degree),
                 my_parallel_projection(end_pos, angle_degree), color);
}

void draw_vertices(struct framebuffer *framebuffer, struct Grid *grid, sfColor color) {
    sfVector3f start_pos = {0, 0, 0};
    sfVector3f end_pos = {0, 0, 0};

    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            start_pos.x = grid->pos.x + j * grid->square_size;
            start_pos.y = grid->pos.y + i * grid->square_size;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + j * grid->square_size;
            end_pos.y = grid->pos.y + i * grid->square_size;
            end_pos.z = grid->pos.z + grid->values[i][j] * grid->square_size * grid->height_factor;
            draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);
        }
    }
}

void draw_roof(struct framebuffer *framebuffer, struct Grid *grid, sfColor color) {
    // join the top of each vertex to the top of the vertex on the right
    sfVector3f start_pos = {0, 0, 0};
    sfVector3f end_pos = {0, 0, 0};

    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            start_pos.x = grid->pos.x + j * grid->square_size;
            start_pos.y = grid->pos.y + i * grid->square_size;
            start_pos.z = grid->pos.z + grid->values[i][j] * grid->square_size * grid->height_factor;

            if (j != grid->cols - 1) {
                end_pos.x = grid->pos.x + (j + 1) * grid->square_size;
                end_pos.y = grid->pos.y + i * grid->square_size;
                end_pos.z = grid->pos.z + grid->values[i][j + 1] * grid->square_size * grid->height_factor;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);
            }
            if (i != grid->rows - 1) {
                end_pos.x = grid->pos.x + j * grid->square_size;
                end_pos.y = grid->pos.y + (i + 1) * grid->square_size;
                end_pos.z = grid->pos.z + grid->values[i + 1][j] * grid->square_size * grid->height_factor;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);
            }
        }
    }
}


void draw_ground(struct framebuffer *framebuffer, struct Grid *grid, sfColor color) {
    sfVector3f start_pos = {0, 0, 0};
    sfVector3f end_pos = {0, 0, 0};

    // draw a grid with horizontal lines and vertical lines
    for (int i = 0; i < grid->rows - 1; i++) {
        for (int j = 0; j < grid->cols - 1; j++) {
            // top horizontal line
            start_pos.x = grid->pos.x + j * grid->square_size;
            start_pos.y = grid->pos.y + i * grid->square_size;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + (j + 1) * grid->square_size;
            end_pos.y = grid->pos.y + i * grid->square_size;
            end_pos.z = grid->pos.z;
            draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);

            // left vertical line
            start_pos.x = grid->pos.x + j * grid->square_size;
            start_pos.y = grid->pos.y + i * grid->square_size;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + j * grid->square_size;
            end_pos.y = grid->pos.y + (i + 1) * grid->square_size;
            end_pos.z = grid->pos.z;
            draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);

            // bottom horizontal line
            if (i == grid->rows - 2) {
                start_pos.x = grid->pos.x + j * grid->square_size;
                start_pos.y = grid->pos.y + (i + 1) * grid->square_size;
                start_pos.z = grid->pos.z;
                end_pos.x = grid->pos.x + (j + 1) * grid->square_size;
                end_pos.y = grid->pos.y + (i + 1) * grid->square_size;
                end_pos.z = grid->pos.z;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);
            }
            // right vertical line
            if (j == grid->cols - 2) {
                start_pos.x = grid->pos.x + (j + 1) * grid->square_size;
                start_pos.y = grid->pos.y + i * grid->square_size;
                start_pos.z = grid->pos.z;
                end_pos.x = grid->pos.x + (j + 1) * grid->square_size;
                end_pos.y = grid->pos.y + (i + 1) * grid->square_size;
                end_pos.z = grid->pos.z;
                draw_parallel_ground_line(framebuffer, start_pos, end_pos, color, grid->parallel_angle_deg);
            }
        }
    }
}
