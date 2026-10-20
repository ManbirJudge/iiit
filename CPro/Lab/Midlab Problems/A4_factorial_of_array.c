#include <stdio.h>

const int P = 1000000007;

int special_factorial(int n) {
    static int cache[1000000] = {0};  // very naive cache, but should work

    if (n <= 1) return 1;

    if (cache[n] == 0)
        cache[n] = ((long long int)n * special_factorial(n - 1)) % P;

    return cache[n];
}

int main(void) {
    int N;
    scanf("%d", &N);

    int a[N];
    for (int i = 0; i < N; i++)
        scanf("%d", a + i);

    int b[N];
    for (int i = 0; i < N; i++)
        b[i] = special_factorial(a[i]);

    for (int i = 0; i < N; i++)
        printf("%d ", b[i]);
    printf("\n");
    
    return 0;
}