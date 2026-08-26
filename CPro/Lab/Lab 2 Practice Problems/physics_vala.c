#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int Fx = 0, Fy = 0, Fz = 0;

    int fx, fy, fz;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &fx, &fy, &fz);

        Fx += fx;
        Fy += fy;
        Fz += fz;
    }
    
    if (Fx == 0 && Fy == 0 && Fz == 0) printf("YES\n");
    else printf("NO\n");

    return 0;
}
