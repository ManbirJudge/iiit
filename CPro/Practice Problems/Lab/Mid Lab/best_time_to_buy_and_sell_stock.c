#include <stdio.h>
#include <limits.h>

int maxProfit(int *prices, int pricesSize) {
    int max_profit = 0;
    int cur_max_profit = 0;

    int y = INT_MAX;  // starting point
    int x = -1;  // ending point

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < y) {  // a number smaller than starting point is found
            y = prices[i];

            if (cur_max_profit > max_profit) max_profit = cur_max_profit;

            x = -1;
            cur_max_profit = 0;
        } else {
            if (prices[i] > x) {  // a number larger than ending point is found
                x = prices[i];
                cur_max_profit = x - y;
            } 
        }
    }

    if (cur_max_profit > max_profit) max_profit = cur_max_profit;

    return max_profit;
}
