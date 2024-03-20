#include <stdio.h>
#include <string.h>

#define MAX_ROWS        100
#define MAX_COLUMNS     100

typedef long long ll;

int rows, columns;
char matrix[MAX_ROWS][MAX_COLUMNS];
int state[2];
int old_state[2];

enum terrain {
    ASH = '.',
    ROCK = '#',
};

int is_column_equal(int a, int b) {
    for (int i = 0; i < rows; i++) {
        if (matrix[i][a] != matrix[i][b]) {
            return 0;
        }
    }
    return 1;
}

int is_row_equal(int a, int b) {
    for (int i = 0; i < columns; i++) {
        if (matrix[a][i] != matrix[b][i]) {
            return 0;
        }
    }
    return 1;
}

int reflection_column() {
    for (int i = columns - 1; i >= 0; i--) {
        int satisfies = 1;
        for (int j = 0; j < columns - i; j++) {
            int x = i - j - 1;
            int y = i + j;
            if (x < 0) {
                continue;
            }
            if (!is_column_equal(x, y)) {
                satisfies = 0;
                break;
            }
        }
        if (satisfies) {
            state[1] = i;
            return i;
        }
    }
    state[1] = -1;
    return -1;
}

int reflection_row() {
    for (int i = rows - 1; i >= 0; i--) {
        int satisfies = 1;
        for (int j = 0; j < rows - i; j++) {
            int x = i - j - 1;
            int y = i + j;
            if (x < 0) {
                continue;
            }
            if (!is_row_equal(x, y)) {
                satisfies = 0;
                break;
            }
        }
        if (satisfies) {
            state[1] = i;
            return i;
        }
    }
    state[1] = -1;
    return -1;
}

ll eval() {
    ll res = 100LL * reflection_row();
    state[0] = 1;
    if (res < 0 || (state[0] == old_state[0] && state[1] == old_state[1])) {
    // if (res < 0) {
        res = reflection_column();
        state[0] = 2;
    }
    if (res < 0) {
        res = 0;
        state[0] = 0;
    }
    return res;
}

ll fix_smudge() {
    ll old_eval = eval();
    old_state[0] = state[0];
    old_state[1] = state[1];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            char old_char = matrix[i][j];
            matrix[i][j] = (old_char == ROCK ? ASH : ROCK);
            ll new_eval = eval();
            matrix[i][j] = old_char;
            if (new_eval) {
                return new_eval;
            }
        }
    }
    return 0;
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input13", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    rows = 0;
    ll ans = 0;
    int index = 0;

    while (fgets(line, 1024, input_file)) {

        if (!strcmp(line, "\n")) {
            index++;
            ll res = fix_smudge();
            if (res == 0) {
                printf("problem at %d\n", index);
            } else {
                // printf("%lld\n", res);
            }
            ans += res;
            rows = 0;
            continue;
        }

        int n = strlen(line);
        columns = n-1;
        for (int i = 0; i < n-1; i++) {
            matrix[rows][i] = line[i];
        }
        rows++;
    }

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < columns; j++) {
    //         printf("%c", matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%lld\n", ans);
}
