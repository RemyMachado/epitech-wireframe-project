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
            *cols = temp_cols + 1;
        }
    }

    fclose(file);
}

struct Grid *init_grid(const char *filename, int rows, int cols) {
    FILE *file;
    // Allocate memory for the grid...
    // ...struct
    struct Grid *grid = (struct Grid *) malloc(sizeof(struct Grid));
    grid->rows = rows;
    grid->cols = cols;
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
            if (col != grid->cols - 1) {
                fscanf(file, ",");
            }
        }
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
    grid = init_grid(argv[1], rows, cols);

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
