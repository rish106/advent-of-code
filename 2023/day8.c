#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 17576

typedef long long ll;

ll gcd(ll a, ll b) {
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (a > b) {
        return gcd(b, a % b);
    } else {
        return gcd(b % a, a);
    }
}

ll lcm(ll a, ll b) {
    return ((a / gcd(a, b)) * b);
}

int all_at_destination(int* nodes, int size) {
    for (int i = 0; i < size; i++) {
        if (nodes[i] % 26 != 25) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char line[1024];
    FILE* input_file = fopen("input8", "r");
    int instructions[1000];
    int size = 0;

    while (fgets(line, 1024, input_file) && strcmp(line, "\n")) {
        int n = strlen(line);
        for (int i = 0; i < n-1; i++) {
            instructions[size] = (line[i] == 'L' ? 0 : 1);
            size++;
        }
    }

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", instructions[i]);
    // }
    // printf("\n");

    int adj[MAX_SIZE][2];
    int curr_nodes[MAX_SIZE / 26];
    int curr_size = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        adj[i][0] = adj[i][1] = -1;
    }

    while (fgets(line, 1024, input_file)) {

        int n = strlen(line);
        int node = 0;
        int i;
        for (i = 0; i < 3; i++) {
            node = 26 * node + (line[i] - 'A');
        }
        if (node % 26 == 0) {
            curr_nodes[curr_size] = node;
            curr_size++;
        }

        while (!isalpha(line[i])) {
            i++;
        }

        for (int j = 0; j < 2; j++) {
            int adj_node = 0;
            while (i < n && isalpha(line[i])) {
                adj_node = 26 * adj_node + (line[i] - 'A');
                i++;
            }
            adj[node][j] = adj_node;
            while (i < n && !isalpha(line[i])) {
                i++;
            }
        }

    }

    long long steps = 0;
    int instruction_num = 0;
    int node_steps[MAX_SIZE / 26] = {0};

    while (!all_at_destination(curr_nodes, curr_size)) {
        steps++;
        for (int i = 0; i < curr_size; i++) {
            if (curr_nodes[i] % 26 == 25) {
                continue;
            }
            curr_nodes[i] = adj[curr_nodes[i]][instructions[instruction_num]];
            if (curr_nodes[i] % 26 == 25) {
                node_steps[i] = steps;
            }
        }
        instruction_num = (instruction_num + 1) % size;
    }

    ll total_steps = 1;
    for (int i = 0; i < curr_size; i++) {
        // printf("%d ", node_steps[i]);
        total_steps = lcm(total_steps, node_steps[i]);
    }

    printf("%lld\n", total_steps);

    return 0;
}
