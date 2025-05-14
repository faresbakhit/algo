#include <bits/stdc++.h>

using namespace std;

class Solution1
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        size_t n = nums.size();
        vector<int> r(n), p(n), s(n);
        int m = 1;
        for (size_t i = 0; i != n; i++)
        {
            p[i] = m;
            m *= nums[i];
        }
        m = 1;
        for (size_t i = n - 1; i != (size_t)-1; i--)
        {
            s[i] = m;
            m *= nums[i];
        }
        for (size_t i = 0; i != n; i++)
        {
            r[i] = p[i] * s[i];
        }
        return r;
    }
};

class Solution2
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        size_t n = nums.size();
        vector<int> r(n);
        int m = 1;
        for (size_t i = 0; i != n; i++)
        {
            r[i] = m;
            m *= nums[i];
        }
        m = 1;
        for (size_t i = n - 1; i != (size_t)-1; i--)
        {
            r[i] *= m;
            m *= nums[i];
        }
        return r;
    }
};