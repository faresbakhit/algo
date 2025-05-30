#pragma once
#include <type_traits>
#include <utility>

// varidic max, min, and minmax implementation

namespace algo {
namespace detail {

// max base case
template <class T>
constexpr T const &do_max(T const &v) {
    return v;
}

// max inductive case
template <class T, class... Rest> // requires SameType<T, Rest...>
constexpr T const &do_max(T const &v0, T const &v1, Rest const &...rest) {
    return do_max(v0 < v1 ? v1 : v0, rest...);
}

// min base case
template <class T>
constexpr T const &do_min(T const &v) {
    return v;
}

// min variadic inductive case
template <class T, class... Rest> // requires SameType<T, Rest...>
constexpr T const &do_min(T const &v0, T const &v1, Rest const &...rest) {
    return do_min(v0 < v1 ? v0 : v1, rest...);
}

// min_max base case
template <class T>
constexpr std::pair<T const &, T const &> do_min_max(T const &cmin, T const &cmax) {
    return {cmin, cmax};
}

// min_max inductive case
template <class T, class... Rest> // requires SameType<T, Rest...>
constexpr std::pair<T const &, T const &> do_min_max(T const &cmin, T const &cmax, T const &next, Rest const &...rest) {
    return do_min_max(cmin < next ? cmin : next, next < cmax ? cmax : next, rest...);
}

} // namespace detail

template <class T, class... Rest>
requires(std::is_same_v<T, Rest> && ...)
inline constexpr T const &min(T const &first, Rest const &...rest) {
    return detail::do_min(first, rest...);
}

template <class T, class... Rest>
requires(std::is_same_v<T, Rest> && ...)
inline constexpr T const &max(T const &first, Rest const &...rest) {
    return detail::do_max(first, rest...);
}

template <class T, class... Rest>
requires(std::is_same_v<T, Rest> && ...)
inline constexpr std::pair<T const &, T const &> min_max(T const &first, Rest const &...rest) {
    return detail::do_min_max(first, first, rest...);
}
} // namespace algo
