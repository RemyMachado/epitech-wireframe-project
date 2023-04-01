#include "projections.h"
#include "my_math.h"
#include <math.h>

// converts a 3D point to a 2D point using the parallel projection
// (angle is in degree):
// TODO: try with matrix transformation

/*
 *
 * Transformation matrix:
 * [1][cos(A)]
 * [0][  1   ]
 * */
sfVector2f my_parallel_projection(sfVector2f pos2d, float angle_deg) {
    float new_x = pos2d.x + pos2d.y * cos(degrees_to_radians(angle_deg + 90));
    float new_y = pos2d.y;

    sfVector2f new_pos2f = {new_x, new_y};

    return new_pos2f;
}

void parallel_projection_test(struct framebuffer *framebuffer) {
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
}


/*
 *
 * Transformation matrix:
 * [cos(30°)][cos(120°)]
 * [sin(30°)][sin(120°)]
 * */
sfVector2f my_isometric_projection(sfVector2f pos2d) {
    float render_offset_x = 350;
    float render_offset_y = 0;

    float angle_unit_x_vector_rad = degrees_to_radians(90 - 60);
    float angle_unit_y_vector_rad = degrees_to_radians(90 + 60);

    float new_x = pos2d.x * cos(angle_unit_x_vector_rad) + pos2d.y * cos(angle_unit_y_vector_rad);
    float new_y = pos2d.x * sin(angle_unit_x_vector_rad) + pos2d.y * sin(angle_unit_y_vector_rad);

    sfVector2f new_pos2f = {new_x + render_offset_x, new_y + render_offset_y};

    return new_pos2f;
}

void isometric_projection_test(struct framebuffer *framebuffer) {
    float square_size = 200;
    sfVector2f start_pos = {0, 0};
    sfVector2f end_pos = {0, 0};

    start_pos.x = 350;
    start_pos.y = 350;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    start_pos.x = 350;
    start_pos.y = 350;
    end_pos.x = 350;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    start_pos.x = 350 + square_size * 2;
    start_pos.y = 350;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    start_pos.x = 350;
    start_pos.y = 350 + square_size;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    start_pos.x = 350;
    start_pos.y = 350 + square_size * 2;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    start_pos.x = 350 + square_size;
    start_pos.y = 350;
    end_pos.x = 350 + square_size;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, start_pos, end_pos, sfWhite);

    /*
     * ISOMETRIC PROJECTION
     * */
    start_pos.x = 350;
    start_pos.y = 350;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);

    start_pos.x = 350;
    start_pos.y = 350;
    end_pos.x = 350;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);

    start_pos.x = 350 + square_size * 2;
    start_pos.y = 350;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);

    start_pos.x = 350;
    start_pos.y = 350 + square_size;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);

    start_pos.x = 350;
    start_pos.y = 350 + square_size * 2;
    end_pos.x = 350 + square_size * 2;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);

    start_pos.x = 350 + square_size;
    start_pos.y = 350;
    end_pos.x = 350 + square_size;
    end_pos.y = 350 + square_size * 2;
    my_draw_line(framebuffer, my_isometric_projection(start_pos), my_isometric_projection(end_pos), sfRed);
}
