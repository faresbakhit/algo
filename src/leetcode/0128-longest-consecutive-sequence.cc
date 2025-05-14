#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    int longestConsecutive(const vector<int> &nums) {
        size_t n = nums.size();
        if (n == 0)
            return 0;
        set<int> s(nums.cbegin(), nums.cend());
        int p = 1, q = 1, r = *s.cbegin();
        for (auto it = next(s.cbegin()); it != s.cend(); it++) {
            if (*it == r + 1)
                p++;
            else
                p = 1;
            q = max(p, q);
            r = *it;
        }
        return q;
    }
};

class Solution2 {
public:
    int longestConsecutive(const std::vector<int> &nums) {
        if (nums.empty())
            return 0;
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;
        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int currentStreak = 1;
                while (numSet.find(num + currentStreak) != numSet.end()) {
                    currentStreak++;
                }
                longestStreak = std::max(longestStreak, currentStreak);
            }
        }
        return longestStreak;
    }
};
