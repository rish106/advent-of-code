#include <stdio.h>
#include <string.h>

int main() {
    char line[1024];
    FILE* input_file = fopen("input2", "r");
    int game_id = 1;
    char* colors[] = {"red", "blue", "green"};
    int color_limits[] = {12, 14, 13};
    int possible_games = 0;
    int sum_of_powers = 0;
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        int i = 0;
        while (line[i] != ':') {
            i++;
        }
        i += 2;
        // printf("%s", line);
        int is_possible = 1;
        int required_cubes[] = {0, 0, 0};
        while (i < n && line[i] != '\n' && line[i] != ';' && is_possible) {
            int num = 0;
            while (line[i] >= '0' && line[i] <= '9') {
                num = 10 * num + (line[i] - '0');
                i++;
            }
            i++;
            char color[8];
            int j;
            for (j = 0; line[i] != '\n' && line[i] != ';' && line[i] != ','; i++, j++) {
                color[j] = line[i];
            }
            color[j] = '\0';
            for (int j = 0; j < 3; j++) {
                // if (!strcmp(color, colors[j]) && num > color_limits[j]) {
                //     is_possible = 0;
                //     break;
                // }
                if (!strcmp(color, colors[j]) && num > required_cubes[j]) {
                    required_cubes[j] = num;
                }
            }
            i += 2;
        }
        // possible_games += is_possible * game_id;
        sum_of_powers += required_cubes[0] * required_cubes[1] * required_cubes[2];
        game_id++;
    }
    // printf("%d\n", possible_games);
    printf("%d\n", sum_of_powers);
    return 0;
}
