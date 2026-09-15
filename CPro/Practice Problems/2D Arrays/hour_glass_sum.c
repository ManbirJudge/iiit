#include <limits.h>

// NOTE: EZ

int hourglassSum(int arr_rows, int arr_columns, int** arr) {
    int S_max = INT_MIN;

    int S;
    for (int i = 1; i < arr_rows - 1; i++) {
        for (int j = 1; j < arr_columns - 1; j++) {
            S = 0;

            for (int i_ = i - 1; i_ <= i + 1; i_++) {
                for (int j_ = j - 1; j_ <= j + 1; j_++) {
                    S += arr[i_][j_];
                }
            }

            S -= arr[i][j - 1];
            S -= arr[i][j + 1];

            if (S > S_max) S_max = S;
        }
    }

    return S_max;
}