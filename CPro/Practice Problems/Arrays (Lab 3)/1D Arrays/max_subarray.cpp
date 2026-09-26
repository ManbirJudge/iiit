#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // TODO: Kadane's algorithm

        size_t n = nums.size();

        int best = INT_MIN;
        
        int sum;
        for (size_t i = 0; i < n; i++) {
            sum = 0;
            for (size_t j = i; j < n; j++) {
                sum += nums[j];
                best = max(best, sum);
            }
        }

        return best;
    }
};