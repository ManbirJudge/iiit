#include <stdio.h>

#define IDX(x, y) (((y) * 8) + (x))

int func(char *board, int x, int y, int queen_c) {
    // placing the queen
    for (int i = 0; i < 8; i++)
        if (board[IDX(i, y)] == '.') board[IDX(i, y)] = '#';
    for (int i = 0; i < 8; i++)
        if (board[IDX(x, i)] == '.') board[IDX(x, i)] = '#';

    // ---
    int c;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[IDX(j, i)] == '*') continue; 
            c += func(board, j, i, 8);
        }
    }


    // removing the queen
    for (int i = 0; i < 8; i++)
        if (board[IDX(i, y)] == '#') board[IDX(i, y)] = '.';
    for (int i = 0; i < 8; i++)
        if (board[IDX(x, i)] == '#') board[IDX(x, i)] = '.';

    // ---
    return c;
}

int main(void) {
    char board[64];
    for (int i = 0; i < 64; i++)
        scanf("%c ", board + i);

    int t_c = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[IDX(j, i)] == '*') continue; 
            t_c += func(board, j, i, 8);
        }
    }

    printf("%d\n", t_c);

    return 0;
}