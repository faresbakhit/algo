// @author Fares A. Bakhit
// @date 2024-10-03
// @description Merge and Quick Sort Implementations

#include <cstdlib>    // size_t
#include <functional> // std::less
#include <utility>    // std::swap

#if __cplusplus > 201703L
#include <numeric> // std::midpoint
#endif

using std::size_t;

namespace algo {

/******************
     Merge Sort
 ******************/

namespace detail {
template <typename T>
T midpoint(T a, T b) {
#if __cplusplus > 201703L
    return std::midpoint(a, b);
#else
    return a + ((b - a) / 2);
#endif // C++20
}

template <typename T, class Compare>
void merge(T *arr, size_t low, size_t mid, size_t high, Compare cmp, T *x, T *y) {
    size_t n = mid - low + 1, m = high - mid;
    for (size_t i = 0; i < n; i++)
        x[i] = arr[low + i];
    for (size_t i = 0; i < m; i++)
        y[i] = arr[mid + i + 1];
    size_t i = 0, j = 0, k = low;
    while (i < n && j < m) {
        if (cmp(x[i], y[j]))
            arr[k++] = x[i++];
        else
            arr[k++] = y[j++];
    }
    while (i < n)
        arr[k++] = x[i++];
    while (j < m)
        arr[k++] = y[j++];
}

template <typename T, class Compare>
void mergeSort(T *arr, size_t low, size_t high, Compare cmp, T *x, T *y) {
    if (low >= high) {
        return;
    }
    // Avoid overflow when computing the midpoint
    size_t mid = midpoint(low, high);
    mergeSort(arr, low, mid, cmp, x, y);
    mergeSort(arr, mid + 1, high, cmp, x, y);
    merge(arr, low, mid, high, cmp, x, y);
}
} // namespace detail

template <typename T, class Compare = std::less<T>>
void mergeSort(T *arr, size_t low, size_t high, Compare cmp = Compare()) {
    size_t mid = detail::midpoint(low, high);
    // Instead of allocating/deallocating over and over again
    // in `detail::merge`, we allocate `x` and `y` only once
    // and we know that `n` and `m` in `detail::merge` will
    // never be larger than the sizes of `x` and `y` here.
    T *x = new int[mid - low + 1], *y = new int[high - mid];
    detail::mergeSort(arr, low, high, cmp, x, y);
    delete[] x;
    delete[] y;
}

template <typename T, class Compare = std::less<T>>
void mergeSort(T *arr, size_t n, Compare cmp = Compare()) {
    mergeSort(arr, 0, n - 1, cmp);
}

/******************
     Quick Sort
 ******************/

namespace detail {
template <typename T, class Compare>
size_t partition(T *arr, size_t low, size_t high, Compare cmp) {
    T pivot = arr[high];
    size_t j = low;
    for (size_t i = low; i < high; i++) {
        if (cmp(arr[i], pivot)) {
            std::swap(arr[i], arr[j++]);
        }
    }
    std::swap(arr[j], arr[high]);
    return j;
}
} // namespace detail

template <typename T, class Compare = std::less<T>>
void quickSort(T *arr, size_t low, size_t high, Compare cmp = Compare()) {
    size_t pivot = detail::partition(arr, low, high, cmp);
    if (pivot > low)
        quickSort(arr, low, pivot - 1, cmp);
    if (pivot < high)
        quickSort(arr, pivot + 1, high, cmp);
}

template <typename T, class Compare = std::less<T>>
void quickSort(T *arr, size_t n, Compare cmp = Compare()) {
    quickSort(arr, 0, n - 1, cmp);
}
} // namespace algo

/************
     Main
 ************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename It>
void printIt(const It &first, const It &last) {
    std::cout << "[";
    It it = first;
    for (; it != last - 1; it++) {
        std::cout << *it << ", ";
    }
    std::cout << *it << "]";
}

int main() {
    std::vector<int> a;
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(a));
    std::vector<int> mergeSortA(a), mergeSortADesc(a), quickSortA(a), quickSortADesc(a);

    algo::mergeSort(mergeSortA.data(), mergeSortA.size());
    algo::mergeSort(mergeSortADesc.data(), mergeSortADesc.size(), std::greater<int>());
    algo::quickSort(quickSortA.data(), quickSortA.size());
    algo::quickSort(quickSortADesc.data(), quickSortADesc.size(), std::greater<int>());

    std::cout << "A = ";
    printIt(a.begin(), a.end());
    std::cout << "\nMerge Sort:\n\tA'  = ";
    printIt(mergeSortA.begin(), mergeSortA.end());
    std::cout << "\n\tA'' = ";
    printIt(mergeSortADesc.begin(), mergeSortADesc.end());
    std::cout << "\nQuick Sort:\n\tA'  = ";
    printIt(quickSortA.begin(), quickSortA.end());
    std::cout << "\n\tA'' = ";
    printIt(quickSortADesc.begin(), quickSortADesc.end());
    std::cout << "\n";
}
