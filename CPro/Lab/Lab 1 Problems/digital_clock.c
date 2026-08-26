#include <stdio.h>

int main(void) {
    int hr, min, sec;
    int k;

    scanf("%d%d%d", &hr, &min, &sec);
    scanf("%d", &k);

    int t_sec = (hr * 3600) + (min * 60) + sec + k;
    t_sec %= (24 * 3600);

    int hr_  = t_sec / 3600;
    int min_ = (t_sec - (hr_ * 3600)) / 60;
    int sec_ = t_sec - ((hr_ * 3600) + (min_ * 60));

    printf("%d %d %d\n", hr_, min_, sec_);

    return 0;
}
