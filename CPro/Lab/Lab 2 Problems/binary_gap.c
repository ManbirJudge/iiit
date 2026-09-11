#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    const int n_bits = sizeof(n) * 8;
    int max_dist = -1;

    int prev_pos = -1;

    for (int i = 0; i < n_bits; i++) {
        if (!((n >> i) & 1)) continue;

        if (prev_pos == -1) {
            prev_pos = i;
            continue;
        }

        int dist = i - prev_pos;
        if (dist > max_dist) max_dist = dist;
        
        prev_pos = i;
    }

    printf("%d\n", max_dist);

    return 0;
}