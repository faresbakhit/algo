#include "sorting.hh"

using namespace algo::sorting;

std::optional<Strategy> algo::sorting::strategy_from(const std::string &s) {
  if (s == "insertion-sort")
    return Strategy::InsertionSort;
  else if (s == "selection-sort")
    return Strategy::SelectionSort;
  else if (s == "std")
    return Strategy::Std;
  else
    return {};
}
