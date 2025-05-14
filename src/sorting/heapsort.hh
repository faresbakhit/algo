#pragma once
#include <cstdlib>    // std::size_t
#include <functional> // std::less
#include <iterator>   // std::distance
#include <utility>    // std::swap

namespace algo::sorting
{
namespace detail
{
template <typename RandomAccessIterator, typename Compare>
void siftDown(RandomAccessIterator it, std::size_t i, std::size_t n, Compare cmp)
{
    std::size_t l = 2 * i + 1, r = 2 * (i + 1), largest = i;
    if (l < n && cmp(it[i], it[l]))
    {
        largest = l;
    }
    if (r < n && cmp(it[largest], it[r]))
    {
        largest = r;
    }
    if (largest != i)
    {
        std::swap(it[i], it[largest]);
        siftDown(it, largest, n, cmp);
    }
}

template <typename RandomAccessIterator, typename Compare>
void heapify(RandomAccessIterator it, size_t n, Compare cmp)
{
    for (size_t i = n / 2; i != (size_t)-1; i--)
    {
        siftDown(it, i, n, cmp);
    }
}
} // namespace detail

template <typename RandomAccessIterator, typename Compare>
void heapsort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
{
    std::size_t n = std::distance(first, last);
    detail::heapify(first, n, cmp);
    for (size_t i = n - 1; i != 0; i--)
    {
        std::swap(first[0], first[i]);
        detail::siftDown(first, 0, i, cmp);
    }
}

template <typename RandomAccessIterator>
void heapsort(RandomAccessIterator first, RandomAccessIterator last)
{
    return heapsort(first, last, std::less());
}
} // namespace algo::sorting
