#pragma once
#include "heapsort.hh"
#include "insertion_sort.hh"
#include "quicksort.hh"
#include "selection_sort.hh"
#include <algorithm>
#include <optional>
#include <string>

namespace algo::sorting
{
enum class Strategy
{
    Heapsort,
    InsertionSort,
    Quicksort,
    SelectionSort,
    Std,
};

std::optional<Strategy> strategy_from(const std::string& s);

template <typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp,
          Strategy strategy)
{
    switch (strategy)
    {
    case Strategy::Heapsort:
        heapsort(first, last, cmp);
        break;
    case Strategy::InsertionSort:
        insertion_sort(first, last, cmp);
        break;
    case Strategy::Quicksort:
        quicksort(first, last, cmp);
        break;
    case Strategy::SelectionSort:
        selection_sort(first, last, cmp);
        break;
    case Strategy::Std:
        std::sort(first, last, cmp);
        break;
    }
}

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, Strategy strategy)
{
    return sort(first, last, std::less(), strategy);
}
} // namespace algo::sorting
