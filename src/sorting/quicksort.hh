#pragma once
#include <functional> // std::less

namespace algo::sorting
{
namespace detail
{
template <typename RandomAccessIterator, class Compare>
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last,
                               Compare cmp)
{
    auto pivot = *(last - 1);
    RandomAccessIterator j = first;
    for (RandomAccessIterator i = first; i != last - 1; i++)
    {
        if (cmp(*i, pivot))
        {
            std::swap(*i, *(j++));
        }
    }
    std::swap(*j, *(last - 1));
    return j;
}
} // namespace detail

template <typename RandomAccessIterator, class Compare>
void quicksort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
{
    if (first == last)
        return;
    RandomAccessIterator pivot = detail::partition(first, last, cmp);
    if (pivot > first)
        quicksort(first, pivot, cmp);
    if (pivot + 1 < last)
        quicksort(pivot + 1, last, cmp);
}

template <typename RandomAccessIterator>
void quicksort(RandomAccessIterator first, RandomAccessIterator last)
{
    quicksort(first, 0, std::distance(first, last) - 1, std::less());
}
} // namespace algo::sorting
