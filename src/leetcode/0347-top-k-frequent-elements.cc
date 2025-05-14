#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    vector<int> topKFrequent(const vector<int> &nums, int k) {
        unordered_map<int, int> um;
        for (int n : nums)
            um[n]++;
        multimap<int, int> m;
        for (const auto &[n, f] : um)
            m.insert({f, n});
        int j = 0;
        vector<int> r(k);
        for (auto it = m.crbegin(); it != m.crend() && j != k; it++)
            r[j++] = it->second;
        return r;
    }
};

class Solution2 {
public:
    vector<int> topKFrequent(const vector<int> &nums, int k) {
        unordered_map<int, int> um;
        for (int n : nums)
            um[n]++;
        priority_queue<pair<int, int>> p;
        for (const auto &[n, f] : um)
            p.push({f, n});
        vector<int> r(k);
        while (k--) {
            r[k] = p.top().second;
            p.pop();
        }
        return r;
    }
};
