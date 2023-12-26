#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char s[1024];
    char* numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    long long sum = 0;
    FILE* input = fopen("input1", "r");
    while (fgets(s, 1024, input)) {
        // printf("%ld\n", strlen(s));
        int n = strlen(s);
        long long val = 0;
        char t[1024];
        for (int i = 0; i < 1023; i++) {
            t[i] = '#';
        }

        // part 1
        // for (int i = 0; i < n; i++) {
        //     if (s[i] >= '0' && s[i] <= '9') {
        //         val += 10 * (s[i] - '0');
        //         break;
        //     }
        // }
        // for (int i = n-1; i >= 0; i--) {
        //     if (s[i] >= '0' && s[i] <= '9') {
        //         val += (s[i] - '0');
        //         break;
        //     }
        // }

        // part 2
        for (int i = 0; i < n; i++) {
            t[i] = s[i];
            int found = 0;
            for (int j = 0; j < 10; j++) {
                if (strstr(t, numbers[j]) != NULL) {
                    val += 10 * j;
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
            
            if (t[i] >= '0' && t[i] <= '9') {
                val += 10 * (t[i] - '0');
                break;
            }
        }

        for (int i = 0; i < 1023; i++) {
            t[i] = '#';
        }

        for (int i = n-1; i >= 0; i--) {
            t[i] = s[i];
            int found = 0;
            for (int j = 0; j < 10; j++) {
                if (strstr(t, numbers[j]) != NULL) {
                    val += j;
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
            
            if (t[i] >= '0' && t[i] <= '9') {
                val += (t[i] - '0');
                break;
            }
        }

        sum += val;
        printf("%lld\n", val);
    }
    printf("%lld\n", sum);
    return 0;
}
