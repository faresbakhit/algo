#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    bool containsDuplicate(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        for (size_t i = 1; i != nums.size(); i++) {
            if (nums[i] == nums[i - 1])
                return true;
        }
        return false;
    }
};

class Solution2 {
public:
    bool containsDuplicate(vector<int> &nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num) > 0)
                return true;
            seen.insert(num);
        }
        return false;
    }
};
