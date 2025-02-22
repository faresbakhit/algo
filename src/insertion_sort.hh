#pragma once
#include <functional>

namespace algo::sorting {
template <typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
                    Compare cmp) {
  for (auto it = first + 1; it < last; it++) {
    auto key = *it;
    RandomAccessIterator jt = it - 1;
    while (cmp(key, *jt)) {
      *(jt + 1) = *jt;
      if (jt == first)
        break;
      jt = jt - 1;
    }
    *(jt + 1) = key;
  }
}

template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
  insertion_sort<RandomAccessIterator>(first, last, std::less());
}
} // namespace algo::sorting