#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int max_w = 0;

        int w;
        for (const auto &accounts_ : accounts) {
            w = accumulate(accounts_.begin(), accounts_.end(), 0);
            if (w > max_w) max_w = w;
        }

        return max_w;
    }
};