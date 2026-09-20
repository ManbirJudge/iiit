#include <stdio.h>

// NOTE: wasn't that hard but... very hard to solve...

int main(void) {
    int n;
    scanf("%d", &n);

    int A[n];

    int T = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        T += A[i];
    }

    int left = 0;
    int right;

    for (int i = 0; i < n; i++) {
        right = T - left - A[i];

        if (left == right) {
            printf("%d\n", i + 1); // 1-indexed output
            return 0;
        }

        left += A[i];
    }

    printf("-1\n");
    return 0;

    // NOTE: only works if all numbers are positive:
    // int i = 0, j = n - 1, s1 = A[0], s2 = A[n - 1];
    //
    // while (j - i != 2) {
    //     printf("%d %d | %d %d | %d\n", i, j, s1, s2, s1 > s2);
    //     if (s1 > s2) {
    //         s2 += A[--j];
    //     } else {
    //         s1 += A[++i];
    //     }
    // }
    //
    // if (s1 == s2) {
    //     printf("%d\n", i + 2);
    // } else {
    //     printf("-1\n");
    // }
}