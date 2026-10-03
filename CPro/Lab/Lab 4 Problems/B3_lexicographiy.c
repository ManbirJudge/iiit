#include <stdio.h>
#include <string.h>

// NOTE: idea is - module index for rotations given the starting point

int main(void) {
    char S[1001];
    scanf("%s", S);

    int n = strlen(S);

    int i_min = 0, i_max = 0;

    for (int i = 0; i < n; i++) {  // for each starting point
        int cmp_min = 0, cmp_max = 0;
        
        for (int j = 0; j < n; j++) {  // for each character, we compare
            if (cmp_min == 0)  // everyting equal till now
                cmp_min += S[(j + i) % n] - S[(j + i_min) % n];

            if (cmp_max == 0)  // everyting equal till now
                cmp_max += S[(j + i) % n] - S[(j + i_max) % n];
        }

        if (cmp_min < 0) i_min = i;
        if (cmp_max > 0) i_max = i;
    }

    for (int j = 0; j < n; j++)
        printf("%c", S[(j + i_min) % n]);
    printf("\n");
    for (int j = 0; j < n; j++)
        printf("%c", S[(j + i_max) % n]);
    printf("\n");

    return 0;
}