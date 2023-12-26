#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARD_RANKS 15

typedef long long ll;

int get_card_rank(char x) {
    switch (x) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 1;
        case 'T':
            return 10;
        default:
            return x - '0';
    }
}

int get_hand_rank(int* x) {

    int cards_for_each_rank[CARD_RANKS] = { 0 };
    int joker_cards = 0;

    for (int i = 1; i < 6; i++) {
        if (x[i] == 1) {
            joker_cards++;
            continue;
        }
        cards_for_each_rank[x[i]]++;
    }

    int occurence_count[6] = { 0 };
    for (int i = 0; i < CARD_RANKS; i++) {
        occurence_count[cards_for_each_rank[i]]++;
    }

    for (int i = 5; i >= 0; i--) {
        if (occurence_count[i] > 0) {
            occurence_count[i + joker_cards]++;
            occurence_count[i]--;
            break;
        }
    }
    
    if (occurence_count[5]) {
        return 6;
    } else if (occurence_count[4]) {
        return 5;
    } else if (occurence_count[3] && occurence_count[2]) {
        return 4;
    } else if (occurence_count[3]) {
        return 3;
    } else if (occurence_count[2] == 2) {
        return 2;
    } else if (occurence_count[2]) {
        return 1;
    }
    return 0;
}

int cmp(const void* a, const void* b) {
    int x = get_hand_rank((int*)a);
    int y = get_hand_rank((int*)b);
    if (x != y) {
        return x - y;
    }
    for (int i = 1; i < 6; i++) {
        x = ((int*)a)[i];
        y = ((int*)b)[i];
        if (x != y) {
            return x - y;
        }
    }
    return 1;
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input7", "r");
    int players[10000][6];
    int size = 0;

    char cards[6];
    int bid;
    while (fgets(line, 1024, input_file)) {
        int n = strlen(line);
        int i = 0;

        for (i = 0; i < 5; i++) {
            cards[i] = line[i];
        }

        while (!isdigit(line[i])) {
            i++;
        }

        bid = 0;
        while (i < n && isdigit(line[i])) {
            bid = 10 * bid + (line[i] - '0');
            i++;
        }

        printf("%s %d\n", cards, bid);
        players[size][0] = bid;
        for (i = 0; i < 5; i++) {
            players[size][i+1] = get_card_rank(cards[i]);
        }
        size++;

    }

    qsort(players, size, sizeof(players[0]), cmp);

    ll ans = 0;
    for (int i = 0; i < size; i++) {
        ans += (ll)(i + 1) * (ll)players[i][0];
        // printf("%d ", get_hand_rank(players[i]));
        // for (int j = 0; j < 6; j++) {
        //     printf("%d ", players[i][j]);
        // }
        // printf("\n");
    }

    printf("%lld\n", ans);
}
