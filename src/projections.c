#include "projections.h"
#include "my_math.h"
#include <math.h>
#include <stdio.h>

// converts a 3D point to a 2D point using the parallel projection
// (angle is in degree):
/*
 *
 * Transformation matrix:
 * [1][cos(A)][0]
 * [0][  1   ][-1]
 * */
sfVector2f my_parallel_projection(sfVector3f pos3d, float angle_deg) {
    float new_x = pos3d.x + pos3d.y * cos(degrees_to_radians(angle_deg + 90));
    float new_y = pos3d.y - pos3d.z;

    sfVector2f new_pos2f = {new_x, new_y};

    // print pos3d and new_pos2f
    //    printf("\n_______\npos3d: (%f, %f, %f)\n", pos3d.x, pos3d.y, pos3d.z);
    //    printf("new_pos2f: (%f, %f)\n", new_pos2f.x, new_pos2f.y);

    return new_pos2f;
}

void parallel_projection_test(struct framebuffer *framebuffer) {
    sfVector3f initial_pos = {500, 500, 0};
    sfVector3f start_pos = {initial_pos.x, initial_pos.y, initial_pos.z};
    sfVector3f end_pos = {initial_pos.x, initial_pos.y, initial_pos.z};

    // top horizontal line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y;
    my_draw_line(framebuffer, (sfVector2f){start_pos.x, start_pos.y}, (sfVector2f){end_pos.x, end_pos.y}, sfWhite);

    // left vertical line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, (sfVector2f){start_pos.x, start_pos.y}, (sfVector2f){end_pos.x, end_pos.y}, sfWhite);

    // right vertical line
    start_pos.x = initial_pos.x + 200;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, (sfVector2f){start_pos.x, start_pos.y}, (sfVector2f){end_pos.x, end_pos.y}, sfWhite);

    // bottom horizontal line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y + 200;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, (sfVector2f){start_pos.x, start_pos.y}, (sfVector2f){end_pos.x, end_pos.y}, sfWhite);


    /*
         * PARALLEL PROJECTION
         * */
    float projection_angle_deg = 30;

    // top horizontal line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y;
    my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                 my_parallel_projection(end_pos, projection_angle_deg), sfRed);

    // left vertical line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                 my_parallel_projection(end_pos, projection_angle_deg), sfRed);

    // right vertical line
    start_pos.x = initial_pos.x + 200;
    start_pos.y = initial_pos.y;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                 my_parallel_projection(end_pos, projection_angle_deg), sfRed);

    // bottom horizontal line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y + 200;
    end_pos.x = initial_pos.x + 200;
    end_pos.y = initial_pos.y + 200;
    my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                 my_parallel_projection(end_pos, projection_angle_deg), sfRed);

    // test Z line
    start_pos.x = initial_pos.x;
    start_pos.y = initial_pos.y;
    start_pos.z = 0;
    end_pos.x = initial_pos.x;
    end_pos.y = initial_pos.y;
    end_pos.z = 200;
    my_draw_line(framebuffer, my_parallel_projection(start_pos, projection_angle_deg),
                 my_parallel_projection(end_pos, projection_angle_deg), sfGreen);
}


/*
 *
 * Transformation matrix:
 * [cos(30°)][cos(120°)][0]
 * [sin(30°)][sin(120°)][-1]
 * */
sfVector2f my_isometric_projection(sfVector3f pos3d, float angle_deg) {
    float angle_unit_x_vector_rad = degrees_to_radians(90 - angle_deg);
    float angle_unit_y_vector_rad = degrees_to_radians(90 + angle_deg);

    float new_x = pos3d.x * cos(angle_unit_x_vector_rad) + pos3d.y * cos(angle_unit_y_vector_rad);
    float new_y = pos3d.x * sin(angle_unit_x_vector_rad) + pos3d.y * sin(angle_unit_y_vector_rad) - pos3d.z;

    sfVector2f new_pos2f = {new_x, new_y};

    return new_pos2f;
}

/*
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

    */
/*
     * ISOMETRIC PROJECTION
     * *//*

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
*/
