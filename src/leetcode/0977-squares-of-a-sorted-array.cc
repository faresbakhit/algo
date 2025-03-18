#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    vector<int> sortedSquares(vector<int> &nums) {
        vector<int> x;
        // Case 1: For all n in nums, n >= 0
        if (nums[0] >= 0) {
            for (int n : nums)
                x.push_back(n *= n);
            return x;
        }
        // Case 2, 3: There exists some n in nums such that n < 0
        auto p = nums.begin();
        auto q = nums.rbegin();
        while (p != nums.end() && *p <= 0)
            p++;
        // Case 2: For all n in nums, n <= 0
        if (p == nums.end()) {
            while (q != nums.rend()) {
                int n = *(q++);
                x.push_back(n * n);
            }
            return x;
        }
        // Case 3: There exists some p,q in nums such that p < 0 and q > 0
        while (q != nums.rend() && *q > 0)
            q++;
        while (true) {
            while (q != nums.rend() && *p > -*q) {
                int n = -*(q++);
                x.push_back(n * n);
            }
            if (q == nums.rend()) {
                while (p != nums.end()) {
                    int n = *(p++);
                    x.push_back(n * n);
                }
                return x;
            }
            while (p != nums.end() && *p <= -*q) {
                int n = *(p++);
                x.push_back(n * n);
            }
            if (p == nums.end()) {
                while (q != nums.rend()) {
                    int n = *(q++);
                    x.push_back(n * n);
                }
                return x;
            }
        }
    }
};
