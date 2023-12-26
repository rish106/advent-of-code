#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("input");
    char x, y;
    long long score = 0;
    while (cin >> x >> y) {
        // part 1
        // if (y == 'X') y = 'A';
        // else if (y == 'Y') y = 'B';
        // else y = 'C';
        // if (x == y) {
        //     score += 3 + (long long)(y) - 64;
        // } else if ((x == 'A' && y == 'B') || (x == 'B' && y == 'C') || (x == 'C' && y == 'A')) {
        //     score += 6 + (long long)(y) - 64;
        // } else {
        //     score += (long long)(y) - 64;
        // }
        if (y == 'X') {
            if (x == 'A') y = 'C';
            else y = x-1;
            score += (long long)(y) - 64;
        } else if (y == 'Z') {
            if (x == 'C') y = 'A';
            else y = x+1;
            score += 6 + (long long)(y) - 64;
        } else {
            y = x;
            score += 3 + (long long)(y) - 64;
        }
    }
    cout << score;
}
