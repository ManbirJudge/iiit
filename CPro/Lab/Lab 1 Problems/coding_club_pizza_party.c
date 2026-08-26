#include <stdio.h>

int main(void) {
    int N, S, P;

    scanf("%d%d%d", &N, &S, &P);
    
    int n_slices = N * S;

    int n_pizza, n_leftover = 0;

    if (n_slices % P == 0) n_pizza = n_slices / P;
    else {
        n_pizza = (n_slices / P) + 1;
        n_leftover = (n_pizza * P) - n_slices;
    }


    printf("%d %d\n", n_pizza, n_leftover);

    return 0;
}
