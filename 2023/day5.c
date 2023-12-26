#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    char line[1024];
    FILE* input_file = fopen("input5", "r");

    ll curr[100][2];
    int size = 0;

    while (fgets(line, 1024, input_file) && strcmp(line, "\n")) {
        int n = strlen(line);
        int i = 7;
        while (i < n) {
            ll num = 0;
            while (isdigit(line[i])) {
                num = 10LL * num + (line[i] - '0');
                i++;
            }
            i++;
            ll range = 0;
            while (isdigit(line[i])) {
                range = 10LL * range + (line[i] - '0');
                i++;
            }
            i++;
            curr[size][0] = num;
            curr[size][1] = range;
            size++;
        }
        // printf("%d ", n);
    }

    while (fgets(line, 1024, input_file)) {
        ll map[100][3];
        int map_sz = 0;
        while (fgets(line, 1024, input_file) && strcmp(line, "\n")) {
            int n = strlen(line);
            int i = 0;
            int j = 0;
            while (i < n) {
                ll num = 0;
                while (isdigit(line[i])) {
                    num = 10LL * num + (ll)(line[i] - '0');
                    i++;
                }
                i++;
                map[map_sz][j] = num;
                j++;
            }
            map_sz++;
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < map_sz; j++) {
                if ((curr[i][0] >= map[j][1]) && (curr[i][0] < map[j][1] + map[j][2])) {
                    ll map_length = map[j][2];
                    ll element_length = curr[i][1];
                    curr[i][0] = map[j][0] + (curr[i][0] - map[j][1]);
                    ll max_destination = map[j][0] + map_length - 1;
                    ll max_element = curr[i][0] + element_length - 1;
                    ll remaining_elements = max_element - max_destination;
                    if (remaining_elements > 0) {
                        curr[size][0] = map[j][1] + map_length;
                        curr[size][1] = remaining_elements - 1;
                        curr[i][1] -= remaining_elements;
                        size++;
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < size; i++) {
            printf("%lld ", curr[i][0]);
        }
        printf("\n\n");
    }

    ll ans = LLONG_MAX;
    for (int i = 0; i < size; i++) {
        if (curr[i][0] < ans) {
            ans = curr[i][0];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
