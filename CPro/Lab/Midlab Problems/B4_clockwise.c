#include <stdio.h>

int main(void) {
    int m, n;
    scanf("%d %d", &m, &n);

    int mat[m][n];

    int min_x = -1;
    int min_y = -1;
    int max_x = n;
    int max_y = m;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    }

    char dir = 'l';
    int cur_x = 0;
    int cur_y = 0;

    for (int i = 0; i < m * n; i++) {
        printf("%d ", mat[cur_y][cur_x]);
        switch (dir) {
            case 'l': {
                if (cur_x == max_x - 1) {
                    dir = 'd';
                    min_y++;

                    cur_y++;
                } else cur_x++;
                break;
            }
            case 'd': {
                if (cur_y == max_y - 1) {
                    dir = 'r';
                    max_x--;

                    cur_x--;
                } else cur_y++;
                break;
            }
            case 'r': {
                if (cur_x == min_x + 1) {
                    dir = 'u';
                    max_y--;

                    cur_y--;
                } else cur_x--;
                break;
            }
            case 'u': {
                if (cur_y == min_y + 1) {
                    dir = 'l';
                    min_x++;

                    cur_x++;
                } else cur_y--;
                break;
            }
        }
    }
    printf("\n");

    return 0;
}