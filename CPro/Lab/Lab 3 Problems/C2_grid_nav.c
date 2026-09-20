#include <stdio.h>

int main(void) {
    long long int m, n;
    long long int x, y;
    int k;

    scanf("%lld %lld", &m, &n);
    scanf("%lld %lld", &x, &y);
    scanf("%d", &k);

    char moves[k + 1];
    scanf("%s", moves);

    int out_of_bounds = 0;

    for (int i = 0; i < k; i++) {
        switch (moves[i]) {
            case 'U': x--; break;
            case 'D': x++; break;
            case 'R': y++; break;
            case 'L': y--; break;
        }
        if ((x < 0 || x >= m) || (y < 0 || y >= n)) {
            out_of_bounds = 1;
            break;
        }
    }

    if (out_of_bounds) printf("-1\n");
    else printf("%lld %lld", x, y);

    return 0;    
}