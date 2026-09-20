#include <stdio.h>

int main(void) {
    long long int n;
    scanf("%lld", &n);

    long long int excitement_scores[n];
    for (long long int i = 0; i < n; i++)
        scanf("%lld", excitement_scores + i);

    long long int max = 0;
    long long int cur = 0;

    for (long long int i = 0; i < n; i++) {
        if (excitement_scores[i] == 0) {
            if (cur > max) max = cur; // check
            cur = 0; // reset
        }

        if (cur == 0)
            cur = excitement_scores[i];
        else
            cur *= excitement_scores[i];
    }
    if (cur > max) max = cur;

    printf("%lld\n", max);

    return 0;
}