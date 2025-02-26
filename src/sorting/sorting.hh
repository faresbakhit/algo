#pragma once
#include "insertion_sort.hh"
#include "selection_sort.hh"
#include <algorithm>
#include <optional>
#include <string>

namespace algo::sorting {
enum class Strategy {
  InsertionSort,
  SelectionSort,
  Std,
};

std::optional<Strategy> strategy_from(const std::string &s);

template <typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare cmp,
          Strategy strategy) {
  switch (strategy) {
  case Strategy::InsertionSort:
    insertion_sort(first, last, cmp);
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
void sort(RandomAccessIterator first, RandomAccessIterator last,
          Strategy strategy) {
  return sort(first, last, std::less(), strategy);
}
} // namespace algo::sorting
