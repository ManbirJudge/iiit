#include <stdio.h>
#include <string.h>

int POS[26][2] = {
    { 5, 10},  // a
    {50, 20},  // b
    {30, 20},  // c
    {25, 10},  // d
    {20,  0},  // e
    {35, 10},  // f
    {45, 10},  // g
    {55, 10},  // h
    {70,  0},  // i
    {65, 10},  // j
    {75, 10},  // k
    {85, 10},  // l
    {70, 20},  // m
    {60, 20},  // n
    {80,  0},  // o
    {90,  0},  // p
    { 0,  0},  // q
    {30,  0},  // r
    {15, 10},  // s
    {40,  0},  // t
    {60,  0},  // u
    {40, 20},  // v
    {10,  0},  // w
    {20, 20},  // x
    {50,  0},  // y
    {10, 20},  // z
};

#define TO_LOWER(x) (((x) >= 'A' && (x) <= 'Z') ? ((x) - 'A' + 'a') : (x))
#define ABS(x) (x >= 0 ? x : -x)

int main(void) {
    char A[100001] = {0};
    char B[100001] = {0};

    scanf("%s", A);
    scanf("%s", B);

    int d = 0;

    size_t n = strlen(A);
    for (size_t i = 0; i < n; i++) {
        int a = TO_LOWER(A[i]) - 'a';
        int b = TO_LOWER(B[i]) - 'a';

        int dx = POS[a][0] - POS[b][0];
        int dy = POS[a][1] - POS[b][1];

        d += ABS(dx) + ABS(dy);
    }

    printf("%.1f\n", d / 10.f);

    return 0;
}