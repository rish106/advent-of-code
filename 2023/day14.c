#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS        200
#define MAX_COLUMNS     200

typedef long long ll;

int rows, columns;
char matrix[MAX_ROWS][MAX_COLUMNS];

enum rocks {
    ROUNDED = 'O',
    CUBE = '#',
    EMPTY = '.',
};

int main() {
    char line[1024];
    FILE* input_file = fopen("input14", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    rows = 0;
    ll ans = 0;

    while (fgets(line, 1024, input_file)) {

        int n = strlen(line);
        columns = n-1;
        for (int i = 0; i < n-1; i++) {
            matrix[rows][i] = line[i];
        }
        rows++;

    }

    for (int j = 0; j < columns; j++) {
        int first_available = 0;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == ROUNDED) {

                assert(first_available <= i);

                matrix[i][j] = EMPTY;
                matrix[first_available][j] = ROUNDED;
                ans += rows - first_available;

                do {
                    first_available++;
                } while (first_available < rows && matrix[first_available][j] == CUBE);

            } else if (matrix[i][j] == CUBE) {
                first_available = i+1;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    printf("%lld\n", ans);
}
