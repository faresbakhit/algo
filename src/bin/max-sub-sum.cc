#include <numeric> // std::midpoint
#include <vector>  // std::vector

namespace algo {

namespace detail {
int max(int a, int b, int c) {
    if (a > b && a > c)
        return a;
    if (b > c)
        return b;
    return c;
}
} // namespace detail

int maxSubSum1(const std::vector<int> &a) {
    int maxSum = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i; j < a.size(); j++) {
            int thisSum = 0;
            for (size_t k = i; k <= j; k++)
                thisSum += a[k];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    return maxSum;
}

int maxSubSum2(const std::vector<int> &a) {
    int maxSum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int thisSum = 0;
        for (size_t j = i; j < a.size(); j++) {
            thisSum += a[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

int maxSubSum3(const std::vector<int> &a, int left, int right) {
    if (left == right) {
        if (a[left] > 0)
            return a[left];
        else
            return 0;
    }
    int center = std::midpoint(left, right);
    int maxLeftSum = maxSubSum3(a, left, center);
    int maxRightSum = maxSubSum3(a, center + 1, right);
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int j = center + 1; j <= right; ++j) {
        rightBorderSum += a[j];
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
    return detail::max(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubSum3(const std::vector<int> &a) {
    return maxSubSum3(a, 0, a.size() - 1);
}

int maxSubSum4(const std::vector<int> &a) {
    int maxSum = 0, thisSum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        thisSum += a[i];
        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}
} // namespace algo

/************
     Main
 ************/

#include <chrono>
#include <iostream>
#include <iterator>

int main() {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;

    int maxSubSum1, maxSubSum2, maxSubSum3, maxSubSum4;
    duration<double, std::milli> ms1, ms2, ms3, ms4;
    system_clock::time_point tp;
    std::vector<int> a;

    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(a));

    tp = high_resolution_clock::now();
    maxSubSum1 = algo::maxSubSum1(a);
    ms1 = high_resolution_clock::now() - tp;

    tp = high_resolution_clock::now();
    maxSubSum2 = algo::maxSubSum2(a);
    ms2 = high_resolution_clock::now() - tp;

    tp = high_resolution_clock::now();
    maxSubSum3 = algo::maxSubSum3(a);
    ms3 = high_resolution_clock::now() - tp;

    tp = high_resolution_clock::now();
    maxSubSum4 = algo::maxSubSum3(a);
    ms4 = high_resolution_clock::now() - tp;

    std::cout << "maxSubSum1(a) = " << maxSubSum1 << " O(n^3) (" << ms1 << ")\n";
    std::cout << "maxSubSum2(a) = " << maxSubSum2 << " O(n^2) (" << ms2 << ")\n";
    std::cout << "maxSubSum3(a) = " << maxSubSum3 << " O(nlog(n)) (" << ms3 << ")\n";
    std::cout << "maxSubSum4(a) = " << maxSubSum4 << " O(n) (" << ms4 << ")\n";
}
