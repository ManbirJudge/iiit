#include <stdio.h>

// NOTE: sliding-window optimization BABY

int main(void) {
    int N;
    scanf("%d", &N);

    int res[N];

    int n, k;
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &n, &k);

        char forecast[n + 1];

        scanf("%s", forecast);

        // ---
        int min_ops = k;

        // ---
        int prev_ops = 0;
        char prev_first = forecast[0];

        for (int l = 0; l < k; l++)
            if (forecast[l] == 'C') prev_ops++;
        if (prev_ops < min_ops) min_ops = prev_ops;

        // ---
        for (int j = 1; j < n - k + 1; j++) {
            int cur_ops = prev_ops;

            if (prev_first == 'C') cur_ops--;
            if (forecast[j + k - 1] == 'C') cur_ops++;

            if (cur_ops < min_ops) min_ops = cur_ops;

            prev_ops = cur_ops;
            prev_first = forecast[j];
        }

        // ---
        res[i] = min_ops;
    }

    for (int i = 0; i < N; i++)
        printf("%d\n", res[i]);

    return 0;
}