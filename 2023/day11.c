#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 200
#define INCREASE_FACTOR 1000000

char matrix[MAX_SIZE][MAX_SIZE];
int rows = 0;
int columns;

void print_matrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_array(int* a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void copy_row(int index) {
    rows++;
    for (int i = rows - 1; i > index; i--) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = matrix[i-1][j];
        }
    }
}

void copy_column(int index) {
    columns++;
    for (int j = columns - 1; j > index; j--) {
        for (int i = 0; i < rows; i++) {
            matrix[i][j] = matrix[i][j-1];
        }
    }
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input11", "r");
    
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        columns = n-1;
        for (int i = 0; i < n-1; i++) {
            matrix[rows][i] = line[i];
        }
        rows++;
    }

    // int empty_rows[MAX_SIZE];
    // int size_empty_rows = 0;
    int is_empty_row[MAX_SIZE] = {0};

    for (int i = 0; i < rows; i++) {
        int is_empty = 1;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == '#') {
                is_empty = 0;
                break;
            }
        }
        is_empty_row[i] = is_empty;
        // if (is_empty) {
        //     empty_rows[size_empty_rows] = i;
        //     size_empty_rows++;
        // }
    }

    // int empty_columns[MAX_SIZE];
    // int size_empty_columns = 0;
    int is_empty_column[MAX_SIZE] = {0};

    for (int j = 0; j < columns; j++) {
        int is_empty = 1;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == '#') {
                is_empty = 0;
                break;
            }
        }
        is_empty_column[j] = is_empty;
        // if (is_empty) {
        //     empty_columns[size_empty_columns] = j;
        //     size_empty_columns++;
        // }
    }

    // print_array(empty_rows, size_empty_rows);
    // print_array(empty_columns, size_empty_columns);

    // for (int i = 0; i < size_empty_rows; i++) {
    //     copy_row(i + empty_rows[i]);
    // }
    // for (int i = 0; i < size_empty_columns; i++) {
    //     copy_column(i + empty_columns[i]);
    // }

    int pref_empty_rows[MAX_SIZE];
    pref_empty_rows[0] = 0;
    for (int i = 1; i < MAX_SIZE; i++) {
        pref_empty_rows[i] = pref_empty_rows[i-1] + is_empty_row[i-1];
    }

    int pref_empty_columns[MAX_SIZE];
    pref_empty_columns[0] = 0;
    for (int i = 1; i < MAX_SIZE; i++) {
        pref_empty_columns[i] = pref_empty_columns[i-1] + is_empty_column[i-1];
    }

    int points[MAX_SIZE * MAX_SIZE][2];
    int curr_size = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == '#') {
                points[curr_size][0] = i;
                points[curr_size][1] = j;
                curr_size++;
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < curr_size; i++) {
        int x1 = points[i][0];
        int y1 = points[i][1];
        for (int j = i+1; j < curr_size; j++) {
            int x2 = points[j][0];
            int y2 = points[j][1];
            long long extra_rows = ((long long)(INCREASE_FACTOR - 1)) * abs(pref_empty_rows[x1] - pref_empty_rows[x2]);
            long long extra_columns = ((long long)(INCREASE_FACTOR - 1)) * abs(pref_empty_columns[y1] - pref_empty_columns[y2]);
            long long distance = (long long)abs(x2 - x1) + (long long)abs(y2 - y1) + extra_rows + extra_columns;
            ans += distance;
            // printf("%lld\n", distance);
        }
    }

    printf("curr_size = %d\n", curr_size);
    printf("%lld\n", ans);
    // print_matrix();

}
