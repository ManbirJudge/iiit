#include <stdio.h>

int main(void) {
    int z;
    long long a, b, c;

    scanf("%d", &z);

    switch (z) {
        case 1: {
            scanf("%lld%lld", &a, &b);

            printf("%s\n", (b % a == 0) ? "YES" : "NO");

            break;
        }
        case 2: {
            scanf("%lld%lld", &a, &b);
            
            printf("%llu\n", b / a);

            break;
        }
        case 3: {
            scanf("%lld%lld%lld", &a, &b, &c);
            
            printf("%llu\n", (b / c) - (a % c == 0 ? 0 : (a / c)));

            break;
        }
    }

    return 0;
}
