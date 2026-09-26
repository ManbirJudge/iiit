#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    bool searchMatrix(vector<vector<int>> &mat, int x) {
        for (const auto &a : mat) {
            if (any_of(
                a.begin(),
                a.end(),
                [x](const int val) {
                    return val == x;
                }
            )) return true;
        }
        return false;
    }
};