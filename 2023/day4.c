#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input4", "r");
    char dump[10];
    int winning_nums[10], my_nums[25];
    int ans = 0;
    int copies[198];
    for (int i = 0; i < 198; i++) {
        copies[i] = 1;
    }
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        int i = 5;
        while (line[i] == ' ') {
            i++;
        }
        int card = 0;
        while (isdigit(line[i])) {
            card = 10 * card + (line[i] - '0');
            i++;
        }
        i += 2;
        int wins_size = 0;
        while (line[i] != '|') {
            int num = 0;
            while (isdigit(line[i])) {
                num = 10 * num + (line[i] - '0');
                i++;
            }
            while (line[i] == ' ') {
                i++;
            }
            winning_nums[wins_size] = num;
            wins_size++;
            // printf("%d ", num);
        }
        while (!isdigit(line[i])) {
            i++;
        }
        int nums_size = 0;
        while (i < n) {
            int num = 0;
            while (isdigit(line[i])) {
                num = 10 * num + (line[i] - '0');
                i++;
            }
            while (i < n && !isdigit(line[i])) {
                i++;
            }
            my_nums[nums_size] = num;
            nums_size++;
            // printf("%d ", num);
        }
        // qsort(winning_nums, wins_size, sizeof(int), cmpfunc);
        // for (int i = 0; i < wins_size; i++) {
        //     printf("%d ", winning_nums[i]);
        // }
        int win_count = 0;
        for (int i = 0; i < nums_size; i++) {
            for (int j = 0; j < wins_size; j++) {
                if (my_nums[i] == winning_nums[j]) {
                    win_count++;
                    break;
                }
            }
        }
        // ans += 1 << (win_count - 1);
        for (int i = card; win_count > 0; i++) {
            if (i == 198) {
                i = card;
            }
            copies[i] += copies[card - 1];
            win_count--;
        }
    }
    for (int i = 0; i < 198; i++) {
        // printf("%d ", copies[i]);
        ans += copies[i];
    }
    printf("%d\n", ans);
    return 0;
}
