#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

#define MAX_RECORDS_SIZE 500
#define MAX_DAMAGED_SIZE 100

char records[MAX_RECORDS_SIZE];
int sz;

int damaged_lengths[MAX_DAMAGED_SIZE];
int sz_lengths;

ll dp[MAX_RECORDS_SIZE][MAX_DAMAGED_SIZE];

enum record {
    OPERATIONAL = '.',
    DAMAGED = '#',
    UNKNOWN = '?',
};

void reset_dp() {
    for (int i = 0; i <= sz; i++) {
        for (int j = 0; j <= sz_lengths; j++) {
            dp[i][j] = -1;
        }
    }
}

void print_dp() {
    for (int i = 0; i <= sz; i++) {
        for (int j = 0; j <= sz_lengths; j++) {
            if (dp[i][j] >= 0) {
                printf("%lld (%d, %d)\n", dp[i][j], i, j);
            }
        }
        /* printf("\n"); */
    }
}

void compute_dp(int i, int j) {
    if (dp[i][j] != -1) {
        return;
    } else if (i == sz) {
        dp[i][j] = (j == sz_lengths);
        return;
    } else if (j == sz_lengths) {
        for (int k = i; k < sz; k++) {
            if (records[k] == DAMAGED) {
                dp[i][j] = 0;
                return;
            }
        }
        dp[i][j] = 1;
        return;
    }

    int length = damaged_lengths[j];
    int z = i + length;
    if (z > sz) {
        dp[i][j] = 0;
        return;
    }

    int has_segment = 1;
    for (int k = i; k < z; k++) {
        if (records[k] == OPERATIONAL) {
            has_segment = 0;
        }
    }

    if (!has_segment && (records[i] == DAMAGED)) {
        dp[i][j] = 0;
        return;
    } else if (!has_segment) {
        compute_dp(i+1, j);
        dp[i][j] = dp[i+1][j];
        return;
    }

    if (z < sz && records[z] == DAMAGED) {
        if (records[i] == UNKNOWN) {
            compute_dp(i+1, j);
            dp[i][j] = dp[i+1][j];
        } else {
            dp[i][j] = 0;
        }
        return;
    }

    z += (z < sz);
    compute_dp(z, j + 1);
    dp[i][j] = dp[z][j+1];

    if (records[i] == UNKNOWN) {
        compute_dp(i+1, j);
        dp[i][j] += dp[i+1][j];
    }
}

void print_array(int* a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d%c", a[i], (i == size - 1 ? '\n' : ' '));
    }
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input12", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    long long ans = 0;

    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        sz = 0;
        
        int i = 0;
        while (i < n && line[i] != ' ') {
            records[sz] = line[i];
            sz++;
            i++;
        }

        while (i < n && !isdigit(line[i])) {
            i++;
        }

        sz_lengths = 0;
        while (i < n) {
            int num = 0;
            while (i < n && isdigit(line[i])) {
                num = 10 * num + (line[i] - '0');
                i++;
            }
            damaged_lengths[sz_lengths] = num;
            sz_lengths++;
            while (i < n && !isdigit(line[i])) {
                i++;
            }
        }

        // modify sizes for part 2
        records[sz] = '?';
        sz++;
        for (int j = sz; j < 5 * sz - 1; j++) {
            records[j] = records[j - sz];
        }
        sz = 5 * sz - 1;

        for (int j = sz_lengths; j < 5 * sz_lengths; j++) {
            damaged_lengths[j] = damaged_lengths[j - sz_lengths];
        }
        sz_lengths *= 5;

        // printf("%s %d\n", records, sz);
        // print_array(damaged_lengths, sz_lengths);
        reset_dp();

        compute_dp(0, 0);
        ans += dp[0][0];
        printf("%lld\n", dp[0][0]);
        
        // print_dp();

        // for (int j = 0; j <= sz; j++) {
        //     free(dp[j]);
        // }
        // free(dp);
    }

    printf("%lld\n", ans);

    return 0;
}
