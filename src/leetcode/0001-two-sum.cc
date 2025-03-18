#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    vector<size_t> twoSum(vector<int> &nums, int target) {
        unordered_map<int, size_t> targetMap;
        for (size_t i = 0; i != nums.size(); i++)
            targetMap[target - nums[i]] = {i};
        for (size_t i = 0; i != nums.size(); i++) {
            auto it = targetMap.find(nums[i]);
            if (it != targetMap.end() && it->second != i) {
                return {i, it->second};
            }
            // alternative for-loop body:
            // if (targetMap.count(nums[i]) != 0 && targetMap[nums[i]] != i) {
            //     return {i, targetMap[nums[i]]};
            // }
        }
        return {};
    }
};

// one pass
class Solution2 {
public:
    vector<size_t> twoSum(vector<int> &nums, int target) {
        unordered_map<int, size_t> targetMap;
        for (size_t i = 0; i != nums.size(); i++) {
            int comp = target - nums[i];
            if (targetMap.count(comp) != 0) {
                return {i, targetMap[comp]};
            }
            targetMap[nums[i]] = i;
        }
        return {};
    }
};
