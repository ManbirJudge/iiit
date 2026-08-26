#include <stdio.h>
#include <string.h>

int main(void) {
    unsigned long long day, month, year, hr, min, sec, mili, micro, nano;
    char am_pm[3];

    scanf("%llu-%llu-%llu %llu:%llu:%llu.%llu.%llu.%llu %s",
        &day,  &month, &year,
        &hr,   &min,   &sec,
        &mili, &micro, &nano,
        am_pm
    );
   
    unsigned long long t_hr = (hr % 12) + (strcmp(am_pm, "PM") == 0 ? 12 : 0);
    unsigned long long t_nano = ((t_hr * 3600 + min * 60 + sec) * 1000000000) + (mili * 1000000) + (micro * 1000) + nano;

    printf("%02llu-%02llu-%02llu %llu\n", year, month, day, t_nano);

    return 0;
}
