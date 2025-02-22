#pragma once

namespace algo::search {
template <typename It, typename Tp>
It linear_search(It first, It last, const Tp &x) {
  while (first < last && *first != x) {
    first = first + 1;
  }
  return first;
}
} // namespace algo::search
