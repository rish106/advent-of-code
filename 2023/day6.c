#include <stdio.h>
#include <string.h>
#include <time.h>

typedef long long ll;

ll function(ll distance, ll total_time, ll button_time) {
    return button_time * (total_time - button_time) - distance;
}

int main(int argc, char *argv[]) {

    ll times[] = {54, 70, 82, 75};
    ll distances[] = {239, 1142, 1295, 1253};

    ll ans = 1;

    // part 1
    // for (int i = 0; i < 4; i++) {
    //     ll num = 0;
    //     for (ll j = 1; j < times[i]; j++) {
    //         num += (function(distances[i], times[i], j) > 0);
    //     }
    //     ans *= num;
    // }

    ll total_time = 54708275;
    ll total_distance = 239114212951253;
    ll num = 0;
    clock_t t; 
    t = clock(); 
    int found_first_zero = 0;
    for (ll j = 1; j < total_time; j++) {
        ll x = function(total_distance, total_time, j);
        num += (x > 0);
    }
    ans *= num;
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("took %f seconds to execute \n", time_taken); 

    printf("ans = %lld\n", ans);

    return 0;
}
