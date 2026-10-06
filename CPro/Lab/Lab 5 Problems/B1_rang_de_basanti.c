#include <stdio.h>

int main(void) { 
    int N;
    scanf("%d", &N);

    int a[N];
    for (int i = 0; i < N; i++)
        scanf("%d", a + i);

    int n0 = 0;    
    int n1 = 0;    
    int n2 = 0;

    for (int i = 0; i < N; i++) {
        switch (a[i]) {
            case 0: n0++; break;
            case 1: n1++; break;
            case 2: n2++; break;
        }
    }

    n1 += n0;
    n2 += n1;

    for (int i = 0; i < N; i++) {
        if (i < n0)      a[i] = 0;
        else if (i < n1) a[i] = 1;
        else if (i < n2) a[i] = 2;
    }

    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}