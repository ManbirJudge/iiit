#include <stdio.h>
#include <float.h>
#include <math.h>

int naive_exhaustive_sol(int a) {
    // only works for perfect squares
    
    for (int i = 0; i * 2 < a; i++)
        if (i * i == a) return i;

    return 0;
}

float naive_exhaustive_sol2(float a) {
    static const float pre = 0.0001;

    float closest = 0.0;
    float min_diff = FLT_MAX;

    float x = 0.0;
   
    int _diff;
    while (((_diff = a - x * x) < min_diff) && (_diff >= 0)) {
        printf("%f %f\n", x, _diff);
        closest = x;
        x += pre;
    }

    return  closest;
}

float bin_search_sol(float a) {
    static const float pre = 0.0001;

    float x = a / 2;

    float _diff;
    while (fabs(_diff = a - x * x) > pre) {
        if (_diff < 0) x *= 0.5;
        else x *= 1.5;

    }

    return x;

} 

float bin_search_sol2(float a) {
    // by gemini

    static const float pre = 0.0001;

    float low = 0.f;
    float high = (a < 1.f) ? 1.f : a;
    
    float mid = 0.f;
    while ((high - low) > pre) {
        mid = low + (high - low) / 2.f;
    
        if (mid * mid > a) high = mid;
        else low = mid;
    }

    return low + (high - low) / 2.f;
}

int main(void) {
    float a = 25;

    printf("%f\n", (float)bin_search_sol(a));
    
    return 0;
}
