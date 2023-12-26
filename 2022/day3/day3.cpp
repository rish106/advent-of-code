#include <bits/stdc++.h>

using namespace std;

// part 1
// int main() {
//     ifstream cin ("input");
//     string s;
//     long long ans = 0;
//     while (cin >> s) {
//         int n = (int)s.size();
//         map<char, bool> cnt;
//         bool pr[200];
//         for (int i = 0; i < 200; i++) pr[i] = false;
//         for (int i = 0; i < n/2; i++) {
//             cnt[s[i]] = false;
//             pr[s[i]] = true;
//         }
//         for (int i = n/2; i < n; i++) {
//             if (!cnt[s[i]] && pr[s[i]]) cnt[s[i]] = true;
//         }
//         for (auto x : cnt) {
//             if (x.second == true) {
//                 if (x.first < 'a') ans += x.first - 'A' + 27;
//                 else ans += x.first - 'a' + 1;
//             }
//         }
//     }
//     cout << ans << endl;
// }


int main() {
    ifstream cin ("input");
    string s;
    int ans = 0;
    while (cin >> s) {
        int n = (int)s.size();
        map<char, bool> cnt;
        bool pr[200];
        for (int i = 0; i < 200; i++) pr[i] = false;
        for (int i = 0; i < n/2; i++) {
            cnt[s[i]] = false;
            pr[s[i]] = true;
        }
        for (int i = n/2; i < n; i++) {
            if (!cnt[s[i]] && pr[s[i]]) cnt[s[i]] = true;
        }
        for (auto x : cnt) {
            if (x.second == true) {
                if (x.first < 'a') ans += x.first - 'A' + 27;
                else ans += x.first - 'a' + 1;
            }
        }
    }
    cout << ans << endl;
}
