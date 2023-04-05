#include "wireframe.h"
#include "matrix_transformations.h"
#include "projections.h"

/*
 * Apply transformations in the following order:
 * 1) Rotation (around the local center)
 * 2) Translation
 *
 * N.B. Scaling is done (before) at local level to not impact the whole 3D space
 * */
sfVector3f apply_all_transformations_3d(sfVector3f initial_vector, struct Grid *grid) {
    float grid_size_x = grid->cols * grid->cube_scaling_axis_factors.x;
    float grid_size_y = grid->rows * grid->cube_scaling_axis_factors.y;
    float grid_size_z = grid->max_value * grid->cube_scaling_axis_factors.z;

    sfVector3f center = {-1 * (grid_size_x / 2), -1 * (grid_size_y / 2), -1 * (grid_size_z / 2)};
    sfVector3f centered_initial_vector = apply_translation_3d(initial_vector, center);

    /* 1) Rotation */
    sfVector3f rotated_vector = apply_rotation_3d_deg(centered_initial_vector, grid->rotation_axes_deg);

    /* 2) Translation */
    sfVector3f translated_vector = apply_translation_3d(rotated_vector, grid->translation_vector);

    return translated_vector;
}

void draw_parallel_line(struct framebuffer *framebuffer, struct Grid *grid, sfVector3f start_pos, sfVector3f end_pos,
                        sfColor from_color, sfColor to_color) {
    float max_height = grid->max_value * grid->cube_scaling_axis_factors.z;

    sfVector3f transformed_start_pos = apply_all_transformations_3d(start_pos, grid);
    sfVector3f transformed_end_pos = apply_all_transformations_3d(end_pos, grid);

    // compute from_color and to_color
    // the color is a gradient with to_color corresponding to `max_height` and from_color to 0
    float start_ratio = start_pos.z / max_height;
    float end_ratio = end_pos.z / max_height;
    sfColor start_color = {(from_color.r + (to_color.r - from_color.r) * start_ratio),
                           from_color.g + (to_color.g - from_color.g) * start_ratio,
                           from_color.b + (to_color.b - from_color.b) * start_ratio,
                           from_color.a + (to_color.a - from_color.a) * start_ratio};

    sfColor end_color = {from_color.r + (to_color.r - from_color.r) * end_ratio,
                         from_color.g + (to_color.g - from_color.g) * end_ratio,
                         from_color.b + (to_color.b - from_color.b) * end_ratio,
                         from_color.a + (to_color.a - from_color.a) * end_ratio};

    my_draw_line_gradient(framebuffer, my_parallel_projection(transformed_start_pos, grid->parallel_angle_deg),
                          my_parallel_projection(transformed_end_pos, grid->parallel_angle_deg), start_color,
                          end_color);
    //    my_draw_line(framebuffer, my_parallel_projection(transformed_start_pos, grid->parallel_angle_deg),
    //                 my_parallel_projection(transformed_end_pos, grid->parallel_angle_deg), color);
}

void draw_vertices(struct framebuffer *framebuffer, struct Grid *grid, sfColor from_color, sfColor to_color) {
    sfVector3f start_pos = {0, 0, 0};
    sfVector3f end_pos = {0, 0, 0};

    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            start_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            start_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            end_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            end_pos.z = grid->pos.z + grid->values[i][j] * grid->cube_scaling_axis_factors.z;
            draw_parallel_line(framebuffer, grid, start_pos, end_pos, from_color, to_color);
        }
    }
}

void draw_roof(struct framebuffer *framebuffer, struct Grid *grid, sfColor from_color, sfColor to_color) {
    // join the top of each vertex to the top of the vertex on the right
    sfVector3f start_pos = {0, 0, 0};
    sfVector3f end_pos = {0, 0, 0};

    for (int i = 0; i < grid->rows; i++) {
        for (int j = 0; j < grid->cols; j++) {
            start_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            start_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            start_pos.z = grid->pos.z + grid->values[i][j] * grid->cube_scaling_axis_factors.z;

            if (j != grid->cols - 1) {
                end_pos.x = grid->pos.x + (j + 1) * grid->cube_scaling_axis_factors.x;
                end_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
                end_pos.z = grid->pos.z + grid->values[i][j + 1] * grid->cube_scaling_axis_factors.z;
                draw_parallel_line(framebuffer, grid, start_pos, end_pos, from_color, to_color);
            }
            if (i != grid->rows - 1) {
                end_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
                end_pos.y = grid->pos.y + (i + 1) * grid->cube_scaling_axis_factors.y;
                end_pos.z = grid->pos.z + grid->values[i + 1][j] * grid->cube_scaling_axis_factors.z;
                draw_parallel_line(framebuffer, grid, start_pos, end_pos, from_color, to_color);
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
            start_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            start_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + (j + 1) * grid->cube_scaling_axis_factors.x;
            end_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            end_pos.z = grid->pos.z;
            draw_parallel_line(framebuffer, grid, start_pos, end_pos, color, color);

            // left vertical line
            start_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            start_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
            start_pos.z = grid->pos.z;
            end_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
            end_pos.y = grid->pos.y + (i + 1) * grid->cube_scaling_axis_factors.y;
            end_pos.z = grid->pos.z;
            draw_parallel_line(framebuffer, grid, start_pos, end_pos, color, color);

            // bottom horizontal line
            if (i == grid->rows - 2) {
                start_pos.x = grid->pos.x + j * grid->cube_scaling_axis_factors.x;
                start_pos.y = grid->pos.y + (i + 1) * grid->cube_scaling_axis_factors.y;
                start_pos.z = grid->pos.z;
                end_pos.x = grid->pos.x + (j + 1) * grid->cube_scaling_axis_factors.x;
                end_pos.y = grid->pos.y + (i + 1) * grid->cube_scaling_axis_factors.y;
                end_pos.z = grid->pos.z;
                draw_parallel_line(framebuffer, grid, start_pos, end_pos, color, color);
            }
            // right vertical line
            if (j == grid->cols - 2) {
                start_pos.x = grid->pos.x + (j + 1) * grid->cube_scaling_axis_factors.x;
                start_pos.y = grid->pos.y + i * grid->cube_scaling_axis_factors.y;
                start_pos.z = grid->pos.z;
                end_pos.x = grid->pos.x + (j + 1) * grid->cube_scaling_axis_factors.x;
                end_pos.y = grid->pos.y + (i + 1) * grid->cube_scaling_axis_factors.y;
                end_pos.z = grid->pos.z;
                draw_parallel_line(framebuffer, grid, start_pos, end_pos, color, color);
            }
        }
    }
}
