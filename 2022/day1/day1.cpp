#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("input1");
    long long a[1000000];
    for (long long i = 0; i < 1000000; i++) a[i] = 0;
    string s, t;
    long long i = 0, n = 1000000;
    while (getline(cin, s)) {
        if (s.empty()) {
            i++;
        } else {
            a[i] += stoi(s);
        }
    }
    sort(a, a+1000000);
    long long ans = a[n-1]+a[n-2]+a[n-3];
    cout << ans;
}
