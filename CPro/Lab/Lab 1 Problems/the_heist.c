#include <stdio.h>

int main(void) {
    int A, B, C, D;
    int M1, M2, M3, M4;

    scanf("%d.%d.%d.%d %d.%d.%d.%d",
        &A,  &B,  &C,  &D,
        &M1, &M2, &M3, &M4
    );
    
    int N1 = A & M1;
    int N2 = B & M2;
    int N3 = C & M3;
    int N4 = D & M4;

    int B1 = A | (M1 ^ 255);
    int B2 = B | (M2 ^ 255);
    int B3 = C | (M3 ^ 255);
    int B4 = D | (M4 ^ 255);

    printf("%d.%d.%d.%d\n%d.%d.%d.%d\n",
        N1, N2, N3, N4,
        B1, B2, B3, B4
    );

    return 0;
}
