#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int> &nums) {
        int n, m;
        n = m = nums[0] == 1;
        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] == 1) {
                if (nums[i] != nums[i - 1]) {
                    m = max(n, m);
                    n = 0;
                }
                n++;
            }
        }
        return max(n, m);
    }
};
