#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {

        int frequencies[100] = {0};

        for (const int n : nums)
            frequencies[n - 1]++;

        int n_eles = 0;
        int max_freq = INT_MIN;
        for (const int n : nums) {
            if (frequencies[n - 1] > max_freq) {
                max_freq = frequencies[n - 1];
                n_eles = 1;
            } else if (frequencies[n - 1] == max_freq) {
                n_eles++;
            }
        }

        return n_eles;
    }
};