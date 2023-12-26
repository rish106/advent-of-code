#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
    char line[1024];
    FILE* input_file = fopen("input3", "r");
    char matrix[140][141];
    int numbers[140][140];
    int rows = 0, columns = 0;
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        columns = n-1;
        for (int i = 0; i < n-1; i++) {
            matrix[rows][i] = line[i];
            numbers[rows][i] = 0;
        }
        rows++;
    }
    int ans = 0;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {

            if (!isdigit(matrix[row][column])) {
                continue;
            }

            int num = 0;
            int is_part_number = 0;
            int start = column - 1;
            for (;column < columns && isdigit(matrix[row][column]); column++) {
                num = 10 * num + (matrix[row][column] - '0');
            }
            int end = column;

            // check row above and row below
            for (int i = row - 1; i < rows && i <= row + 1; i += 2) {
                for (int j = start; j <= end; j++) {
                    if (i >= 0 && j >= 0 && j < columns && !isdigit(matrix[i][j]) && matrix[i][j] != '.') {
                        is_part_number = 1;
                        break;
                    }
                }
            }

            // check columns left and right
            if (start >= 0 && !isdigit(matrix[row][start]) && matrix[row][start] != '.') {
                is_part_number = 1;
            }
            if (end < columns && !isdigit(matrix[row][end]) && matrix[row][end] != '.') {
                is_part_number = 1;
            }

            if (is_part_number) {
                for (int j = start + 1; j < end; j++) {
                    numbers[row][j] = num;
                }
            }
            // ans += is_part_number * num;
            // printf("%d\n", is_part_number * num);

        }
    }
    // printf("%d\n", ans);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {

            if (matrix[row][column] != '*') {
                continue;
            }

            int surrounding_nums[6];
            int curr_size = 0;

            // check rows above and below
            for (int i = row - 1; i <= row + 1 && i < rows; i += 2) {
                for (int j = column - 1; j <= column + 1 && j < columns; j++) {
                    if (i >= 0 && j >= 0 && (j == column - 1 || numbers[i][j] != numbers[i][j-1]) && (numbers[i][j] > 0)) {
                        surrounding_nums[curr_size] = numbers[i][j];
                        curr_size++;
                    }
                }
            }

            // check columns left and right
            if (column >= 1 && numbers[row][column - 1] > 0) {
                surrounding_nums[curr_size] = numbers[row][column - 1];
                curr_size++;
            }
            if (column < columns - 1 && numbers[row][column + 1] > 0) {
                surrounding_nums[curr_size] = numbers[row][column + 1];
                curr_size++;
            }

            int num = 1;
            for (int i = 0; i < curr_size && curr_size == 2; i++) {
                num *= surrounding_nums[i];
            }
            ans += (curr_size == 2) * num;
        }
    }
    printf("%d\n", ans);
    return 0;
}
