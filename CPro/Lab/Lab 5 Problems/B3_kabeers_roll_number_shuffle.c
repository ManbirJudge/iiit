#include <stdio.h>

int sod(int n) {
    int s = 0;

    while (n > 0) {
        s += n % 10;
        n /= 10;
    }

    return s;
}

int custom_cmp(int a, int b) {
    return (sod(a) < sod(b)) || ((sod(a) == sod(b)) && (a < b));
}

int sort(int *a, int N, int (*cmp)(int a, int b)) {
    int swaps = 0;

    for (int i = 0; i < N - 1; i++) {
        int idx_min = i;
        int min = a[i];

        for (int j = i + 1; j < N; j++) {
            if (cmp(a[j], min)) {
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
    int N;
    scanf("%d", &N);

    int a[N];
    for (int i = 0; i < N; i++)
        scanf("%d", a + i);

    int min_swaps = sort(a, N, custom_cmp);
    
    printf("%d\n", min_swaps);

    return 0;
}