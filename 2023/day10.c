#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

enum direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

enum pipe { 
    GROUND,
    NORTH_SOUTH,
    EAST_WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_WEST,
    SOUTH_EAST,
    START
};

enum pipe get_direction(char x) {
    switch (x) {
        case '|':
            return NORTH_SOUTH;
        case '-':
            return EAST_WEST;
        case 'L':
            return NORTH_EAST;
        case 'J':
            return NORTH_WEST;
        case '7':
            return SOUTH_WEST;
        case 'F':
            return SOUTH_EAST;
        case '.':
            return GROUND;
        default:
            return START;
    }
}

void change_by_direction(enum direction d, int* i, int* j) {
    switch (d) {
        case NORTH:
            --(*i);
            break;
        case SOUTH:
            ++(*i);
            break;
        case EAST:
            ++(*j);
            break;
        case WEST:
            --(*j);
            break;
    }
}

int find_adj(int pipes[140][140], int rows, int columns, int i, int j) {
    if (i >= 1 && (pipes[i-1][j] == NORTH_SOUTH || pipes[i-1][j] == SOUTH_WEST || pipes[i-1][j] == SOUTH_EAST)) {
        return NORTH;
    } else if (i < rows - 1 && (pipes[i+1][j] == NORTH_SOUTH || pipes[i+1][j] == NORTH_WEST || pipes[i+1][j] == NORTH_EAST)) {
        return SOUTH;
    } else if (j >= 1 && (pipes[i][j-1] == EAST_WEST || pipes[i][j-1] == SOUTH_EAST || pipes[i][j-1] == NORTH_EAST)) {
        return WEST;
    } else if (j < columns - 1 && (pipes[i][j+1] == EAST_WEST || pipes[i][j+1] == SOUTH_WEST || pipes[i][j+1] == NORTH_WEST)) {
        return EAST;
    } else {
        return -1;
    }
}

int adj_direction(int pipes[140][140], int rows, int columns, int i, int j, enum direction prev) {
    switch (pipes[i][j]) {
        case NORTH_SOUTH:
            return (prev == NORTH ? NORTH : SOUTH);
        case NORTH_WEST:
            return (prev == EAST ? NORTH : WEST);
        case NORTH_EAST:
            return (prev == WEST ? NORTH : EAST);
        case SOUTH_WEST:
            return (prev == EAST ? SOUTH : WEST);
        case SOUTH_EAST:
            return (prev == WEST ? SOUTH : EAST);
        case EAST_WEST:
            return (prev == WEST ? WEST : EAST);
        default:
            return -1;
    }
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input10", "r");

    int pipes[140][140];
    int visited[140][140];
    int rows = 0;
    int columns;

    ll ans = 0;
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        columns = n-1;
        for (int i = 0; i < n-1; i++) {
            pipes[rows][i] = get_direction(line[i]);
        }
        rows++;
    }

    int start_row, start_column;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (pipes[i][j] == START) {
                start_row = i;
                start_column = j;
            }
            visited[i][j] = 0;
            // printf("%d ", pipes[i][j]);
        }
        // printf("\n");
    }

    int direction = find_adj(pipes, rows, columns, start_row, start_column);
    int i = start_row, j = start_column;
    visited[i][j] = 1;
    // printf("%d %d %d\n", i, j, direction);
    change_by_direction(direction, &i, &j);
    // printf("%d %d\n", i, j);
    int max_distance = 1;
    ans = 1;

    while (!visited[i][j]) {
        visited[i][j] = 1;
        direction = adj_direction(pipes, rows, columns, i, j, direction);
        // printf("%d %d %d\n", i, j, direction);
        change_by_direction(direction, &i, &j);
        // ans++;
    }
    // ans /= 2;

    ans = 0;
    for (int x = 1; x < rows - 1; x++) {
        for (int y = 1; y < columns - 1; y++) {
            if (pipes[x][y] != GROUND) {
                continue;
            }
            int coincide = 0;
            for (int k = x+1; k < rows; k++) {
                if (visited[k][y] && pipes[k][y] == EAST_WEST) {
                    coincide++;
                }
            }
            if (coincide % 2) {
                printf("%d %d\n", x, y);
                ans++;
                break;
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}
