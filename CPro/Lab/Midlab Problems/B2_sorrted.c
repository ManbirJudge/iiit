#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    long long int x[n];

    for (int i = 0; i < n; i++)
        scanf("%lld", x + i);

    long long int n_moves = 0;

    long long int diff;
    for (int i = 1; i < n; i++) {
        if (x[i] >= x[i - 1]) continue;

        diff = x[i - 1] - x[i];

        n_moves += diff;
        x[i] += diff;
    }

    printf("%lld\n", n_moves);

    return 0;
}