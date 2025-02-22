#pragma once
#include <functional>
#include <utility>

namespace algo::sorting {
template <typename RandomAccessIterator, typename Compare>
void selection_sort(RandomAccessIterator first, RandomAccessIterator last,
                    Compare cmp) {
  for (RandomAccessIterator it = first; it != last; it++) {
    RandomAccessIterator key = it;
    for (RandomAccessIterator jt = it + 1; jt < last; jt++) {
      if (cmp(*jt, *key)) {
        key = jt;
      }
    }
    std::swap(*it, *key);
  }
}

template <typename RandomAccessIterator>
void selection_sort(RandomAccessIterator first, RandomAccessIterator last) {
  return selection_sort(first, last, std::less());
}
} // namespace algo::sorting