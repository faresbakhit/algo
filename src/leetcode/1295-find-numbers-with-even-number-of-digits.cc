#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findNumbers(vector<int> &nums) {
        int m = 0;
        for (int n : nums) {
            m += !(numberOfDigits(n) & 1);
        }
        return m;
    }

    int numberOfDigits(int n) {
        int d = 1;
        while ((n /= 10) != 0) {
            d++;
        }
        return d;
    }
};
