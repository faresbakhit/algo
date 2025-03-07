#pragma once
#include <fmt/ranges.h>
#include <functional>

namespace algo::sorting {
template <typename RandomAccessIterator, typename Compare>
void insertion_sort(const RandomAccessIterator &first, const RandomAccessIterator &last, Compare cmp) {
    if (first == last)
        return;

    RandomAccessIterator j;

    for (RandomAccessIterator p = first + 1; p != last; ++p) {
        fmt::println("[{}]", fmt::join(first, last, " "));
        auto tmp = std::move(*p);
        for (j = p; j != first && cmp(tmp, *(j - 1)); --j) {
            *j = std::move(*(j - 1));
        }
        *j = std::move(tmp);
    }
}

template <typename RandomAccessIterator>
void insertion_sort(const RandomAccessIterator &first, const RandomAccessIterator &last) {
    insertion_sort<RandomAccessIterator>(first, last, std::less<decltype(*first)>());
}
} // namespace algo::sorting