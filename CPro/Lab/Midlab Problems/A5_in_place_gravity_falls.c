#include <stdio.h>

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    char grid[N][M];
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }

    for (int i = N - 2; i >= 0; i--) {  // moving from bottom up
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != 'o') continue;

            int k;
            for (k = i; k < N - 1; k++) {
                if (grid[k + 1][j] != '.') break;
            }

            grid[i][j] = '.';
            grid[k][j] = 'o';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%c", grid[i][j]);
        printf("\n");
    }

    return 0;
}