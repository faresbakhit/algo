#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, size_t> sset;
        unordered_map<char, size_t> tset;
        for (char c : s)
            sset[c]++;
        for (char c : t)
            tset[c]++;
        return sset == tset;
    }
};

class Solution2 {
public:
    bool isAnagram(string s, string t) {
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
};
