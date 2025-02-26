#pragma once
#include <functional>
#include <iterator>

namespace algo::sorting {
template <typename RandomAccessIterator, typename Compare>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
                    Compare cmp) {
  using value_type = std::iterator_traits<RandomAccessIterator>::value_type;
  for (RandomAccessIterator it = first + 1; it < last; it++) {
    value_type key = *it;
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