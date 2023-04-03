#include "draw.h"
#include "projections.h"
#include "window.h"
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

int **init_grid(const char *filename, int rows, int cols) {
    FILE *file;
    int row, col;
    // Allocate memory for the grid
    int **grid = (int **) malloc(rows * sizeof(int *));

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file \"%s\".\n", filename);
        exit(EXIT_FAILURE);
    }

    // allocate columns memory
    for (row = 0; row < rows; row++) {
        grid[row] = (int *) malloc(cols * sizeof(int));
    }

    // Read the values into the grid
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            fscanf(file, "%d", &grid[row][col]);
            if (col != cols - 1) {
                fscanf(file, ",");
            }
        }
    }

    fclose(file);

    return grid;
}

void free_grid(int **grid, int rows) {
    int row;

    for (row = 0; row < rows; row++) {
        free(grid[row]);
    }
    free(grid);
}

int main(int argc, char **argv) {
    int row, col, rows, cols;
    int **grid;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    count_rows_cols(argv[1], &rows, &cols);
    grid = init_grid(argv[1], rows, cols);

    // Output the grid
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }

    run_window_loop();

    free_grid(grid, rows);

    return EXIT_SUCCESS;
}
