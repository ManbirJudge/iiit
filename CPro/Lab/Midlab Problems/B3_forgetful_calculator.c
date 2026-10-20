#include <stdio.h>

int main(void) {
    int N, K;
    scanf("%d %d", &N, &K);

    long long int lim = 1;
    for (int i = 0; i < K; i++)
        lim *= 10;

    long long int res = 1;

    long long int cur;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &cur);

        long long int tmp = res * cur;

        if (tmp < res || tmp >= lim) res = 1;
        else res = tmp;
    }

    printf("%lld\n", res);

    return 0;
}