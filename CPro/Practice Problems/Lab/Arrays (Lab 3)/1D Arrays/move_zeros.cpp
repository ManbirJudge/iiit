#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t n = nums.size(); 
        size_t pos = 0;

        for (size_t i = 0; i < n; i++)
            if (nums[i] != 0) nums[pos++] = nums[i];

        for (; pos < n; pos++)
            nums[pos] = 0;
    }
};