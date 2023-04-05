#include "draw.h"
#include "projections.h"
#include "window.h"
#include "wireframe.h"
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

void count_rows_cols(const char *filename, int *rows, int *cols) {
    FILE *file;
    char ch;
    int temp_cols = 0;

    *rows = 0;
    *cols = -1;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file \"%s\".\n", filename);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ',' && *cols == -1) {
            temp_cols++;// will only compute the first row
        } else if (ch == '\n') {
            *rows += 1;
            *cols = temp_cols;
        }
    }

    fclose(file);
}

struct Grid *init_grid(const char *filename, int rows, int cols, float parallel_angle_deg, float isometric_angle_deg,
                       sfVector3f pos, sfVector3f cube_scaling_axis_factors, sfVector3f rotation_axes_deg,
                       sfVector3f translation_vector, sfVector2f (*projector_3d_to_2d)(struct Grid *, sfVector3f)) {
    FILE *file;
    // Allocate memory for the grid...
    // ...struct
    struct Grid *grid = (struct Grid *) malloc(sizeof(struct Grid));
    grid->rows = rows;
    grid->cols = cols;
    grid->max_value = 0;
    grid->parallel_angle_deg = parallel_angle_deg;
    grid->isometric_angle_deg = isometric_angle_deg;
    grid->pos = pos;
    grid->cube_scaling_axis_factors = cube_scaling_axis_factors;
    grid->rotation_axes_deg = rotation_axes_deg;
    grid->translation_vector = translation_vector;
    grid->projector_3d_to_2d = projector_3d_to_2d;
    // ...rows
    grid->values = (int **) malloc(rows * sizeof(int *));
    // ...columns
    for (int row = 0; row < grid->rows; row++) {
        grid->values[row] = (int *) malloc(cols * sizeof(int));
    }


    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file \"%s\".\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read the values into the grid
    for (int row = 0; row < grid->rows; row++) {
        for (int col = 0; col < grid->cols; col++) {
            fscanf(file, "%d", &grid->values[row][col]);
            fscanf(file, ",");
            grid->max_value = max(grid->max_value, grid->values[row][col]);
        }
        fscanf(file, "\n");
    }

    fclose(file);

    return grid;
}

void free_grid(struct Grid *grid) {
    int row;

    for (row = 0; row < grid->rows; row++) {
        free(grid->values[row]);
    }
    free(grid->values);
    free(grid);
}

int main(int argc, char **argv) {
    int row, col, rows, cols;
    struct Grid *grid;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    count_rows_cols(argv[1], &rows, &cols);

    // print the number of rows and columns
    printf("rows: %d, cols: %d\n", rows, cols);

    grid = init_grid(argv[1], rows, cols, 45, 60, (sfVector3f){0, 0, 0}, (sfVector3f){50, 50, 50},
                     (sfVector3f){0, 0, 0}, (sfVector3f){800, 500, 0}, &my_parallel_grid_projection);

    // Output the grid
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            printf("%d ", grid->values[row][col]);
        }
        printf("\n");
    }

    run_window_loop(grid);

    free_grid(grid);

    return EXIT_SUCCESS;
}
