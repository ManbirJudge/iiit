#include <stdbool.h>

// NOTE: I am proud of myself because I thought it myself and did it under 5 minutes on the first try

bool checkPowersOfThree(int n) {
    int r;
    while (n > 0) {
        r = n % 3;

        if (!(r == 0 || r == 1))
            return false;

        n /= 3;
    }

    return true;
}

// LOGIC: we check the remainder as if we are converting the number to base 3.
// if all remainders are 0 or 1, its fine because that would mean, the n = sum of powers of 3
// else, n = sum of powers of 3 multiplied by coefficients

// valid case:
// 91/3 30 1
// 30/3 10 0
// 10/3  3 1
// 3/3   1 0
// 1/3   0 1
// 
// 91 = 3^0 + 3^2 + 3^4
// 
// invalid case:
// 21/3  7 0
// 7/3   2 1
// 2/3   0 2
// 
// 21 = 2 * 3^2 + 3^1