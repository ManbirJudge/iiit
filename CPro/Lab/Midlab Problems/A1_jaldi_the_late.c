#include <stdio.h>

int main(void) {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    long long int A[n][m];
    long long int B[m][p];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            scanf("%lld", &A[i][j]);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++)
            scanf("%lld", &B[i][j]);
    }

    long long int C[n][p];

    long long int _s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            _s = 0;
            for (int k = 0; k < m; k++)
                _s += A[i][k] * B[k][j];

            C[i][j] = _s;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++)
            printf("%lld ", C[i][j]);
        printf("\n");
    }

    return 0;
}