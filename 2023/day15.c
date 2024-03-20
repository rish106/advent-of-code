#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100000

int main(int argc, char *argv[]) {
    char s[MAX_SIZE];
    long long sum = 0;
    FILE* input = fopen("input15", "r");
    while (fgets(s, MAX_SIZE, input)) {
        int n = strlen(s);
        int i = 0;

        while (i < n) {
            long long val = 0;
            while (i < n && s[i] != ',' && s[i] != '\n') {
                val = ((val + s[i]) * 17LL) % 256LL;
                i++;
            }
            sum += val;
            i++;
        }

    }
    printf("%lld\n", sum);
    return 0;
}
