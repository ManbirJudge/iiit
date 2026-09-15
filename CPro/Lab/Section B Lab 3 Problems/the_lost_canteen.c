#include <limits.h>
#include <stdio.h>

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    int A[N * M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i * M + j]);
        }
    }

    int S_max = INT_MIN;
    int I = -1, J = -1;

    int S;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            S = 0;

            for (int i_ = i - 1; i_ <= i + 1; i_++) {
                for (int j_ = j - 1; j_ <= j + 1; j_++) {
                    S += A[i_ * M + j_];
                }
            }

            if (S > S_max) {
                S_max = S;
                I = i;
                J = j;
            }
        }
    }

    printf("%d %d %d\n", I + 1, J + 1, S_max);

    return 0;
}