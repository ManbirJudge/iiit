#include <stdio.h>

long long int sort(long long int *a, long long int N) {
    long long int swaps = 0;

    for (long long int i = 0; i < N - 1; i++) {
        long long int idx_min = i;
        long long int min = a[i];

        for (long long int j = i + 1; j < N; j++) {
            if (a[j] < min) {
                idx_min = j;
                min = a[j];
            }
        }

        if (idx_min == i) continue;

        a[idx_min] = a[i];
        a[i] = min;

        swaps++;
    }

    return swaps;
}

int main(void) { 
    long long int N;
    scanf("%lld", &N);

    long long int a[N];
    for (long long int i = 0; i < N; i++)
        scanf("%lld", a + i);

    long long int min_swaps = sort(a, N);
    
    printf("%lld\n", min_swaps);

    return 0;
}