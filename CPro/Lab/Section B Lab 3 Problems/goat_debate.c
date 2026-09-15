#include <stdio.h>

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    int C[N]; // map    of i-th match
    int S[N]; // rating of i-th match

    int max_ratings[M];  // max rating of k-th map

    for (int i = 0; i < N; i++)
        scanf("%d %d", &C[i], &S[i]);

    for (int i = 0; i < M; i++)
        max_ratings[i] = -1;

    for (int i = 0; i < N; i++) {
        if (S[i] > max_ratings[C[i] - 1])
            max_ratings[C[i] - 1] = S[i];
    }
    
    for (int i = 0; i < M; i++)
        printf("%d ", max_ratings[i]);
    printf("\n");

    return 0;
}