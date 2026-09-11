#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    long long int ans = 0;

    long long int tmp;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &tmp);
        ans ^= tmp;
    }

    printf("%lld\n", ans);
}