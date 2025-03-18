#include <bits/stdc++.h>

using namespace std;

class Solution1 {

    bool isAnagram(const string &s, const string &t) {
        if (s.length() != t.length())
            return false;
        size_t set[26] = {0};
        for (size_t i = 0; i != s.length(); i++) {
            set[s[i] - 'a']++;
            set[t[i] - 'a']--;
        }
        for (size_t i = 0; i != 26; i++) {
            if (set[i] != 0)
                return false;
        }
        return true;
    }

public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        vector<vector<string>> res;
        while (!strs.empty()) {
            vector<string> subRes;
            subRes.push_back(strs[0]);
            for (auto it = next(strs.begin()); it != strs.end(); it++) {
                if (isAnagram(subRes[0], *it)) {
                    subRes.push_back(*it);
                }
            }
            for (const auto &s : subRes) {
                strs.erase(remove(strs.begin(), strs.end(), s), strs.end());
            }
            res.push_back(subRes);
        }
        return res;
    }
};

class Solution2 {

    bool isAnagram(const string &s, const string &t) {
        if (s.length() != t.length())
            return false;
        size_t set[26] = {0};
        for (size_t i = 0; i != s.length(); i++) {
            set[s[i] - 'a']++;
            set[t[i] - 'a']--;
        }
        for (size_t i = 0; i != 26; i++) {
            if (set[i] != 0)
                return false;
        }
        return true;
    }

public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        size_t n = strs.size();
        vector<vector<string>> res;
        bool *collected = new bool[n];
        for (size_t i = 0; i < n; i++) {
            collected[i] = false;
        }
        for (size_t i = 0; i < n; i++) {
            if (collected[i] == false) {
                vector<string> subRes = {strs[i]};
                collected[i] = true;
                for (size_t j = i + 1; j < n; j++) {
                    if (collected[j] == false && isAnagram(strs[i], strs[j])) {
                        subRes.push_back(strs[j]);
                        collected[j] = true;
                    }
                }
                res.push_back(subRes);
            }
        }
        delete[] collected;
        return res;
    }
};

class Solution3 {
    struct ArrayHasher {
        size_t operator()(const std::array<int, 26> &a) const {
            size_t h = 0;
            for (auto e : a)
                h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };

public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<array<int, 26>, vector<string>, ArrayHasher> m;
        for (const string &s : strs) {
            array<int, 26> freq = {0};
            for (char c : s)
                freq[c - 'a']++;
            m[freq].push_back(s);
        }
        vector<vector<string>> res;
        res.reserve(m.size());
        for (auto &p : m) {
            res.push_back(std::move(p.second));
        }
        return res;
    };
};
