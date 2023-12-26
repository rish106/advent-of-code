#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

ll* create_diff_array(ll* arr, int size) {
    ll* diff = malloc((size - 1) * sizeof(ll));
    for (int i = 0; i < size - 1; i++) {
        diff[i] = arr[i+1] - arr[i];
    }
    return diff;
}

int all_equal(ll* arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i-1]) {
            return 0;
        }
    }
    return 1;
}

ll get_next_value(ll* arr, int size) {
    if (all_equal(arr, size)) {
        return arr[0];
    }
    ll* diff = create_diff_array(arr, size);
    ll next_diff = get_next_value(diff, size - 1);
    free(diff);
    return arr[size - 1] + next_diff;
}

ll get_prev_value(ll* arr, int size) {
    if (all_equal(arr, size)) {
        return arr[0];
    }
    ll* diff = create_diff_array(arr, size);
    ll prev_diff = get_prev_value(diff, size - 1);
    free(diff);
    return arr[0] - prev_diff;
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input9", "r");

    ll ans = 0;
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        int i = 0;
        ll sequence[1000];
        int size = 0;
        while (i < n) {
            ll num = 0;
            ll is_positive = 1;
            while (i < n && (line[i] != ' ' && line[i] != '\n')) {
                if (line[i] == '-') {
                    is_positive = -1;
                } else if (isdigit(line[i])) {
                    num = 10LL * num + (line[i] - '0');
                }
                i++;
            }
            num *= is_positive;
            sequence[size] = num;
            size++;
            while (i < n && (line[i] == ' ' || line[i] == '\n')) {
                i++;
            }
        }

        // part 1
        // ll num = get_next_value(sequence, size);

        // part 2
        ll num = get_prev_value(sequence, size);
        // printf("%lld\n", num);
        ans += num;

        // for (int j = 0; j < size; j++) {
        //     printf("%lld ", sequence[j]);
        // }
        // printf("\n");
    }
    printf("%lld\n", ans);
    return 0;
}
