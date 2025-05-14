#include "sorting.hh"

using namespace algo::sorting;

std::optional<Strategy> algo::sorting::strategy_from(const std::string& s)
{
    if (s == "heapsort")
        return Strategy::Heapsort;
    else if (s == "insertion-sort")
        return Strategy::InsertionSort;
    else if (s == "quicksort")
        return Strategy::Quicksort;
    else if (s == "selection-sort")
        return Strategy::SelectionSort;
    else if (s == "std")
        return Strategy::Std;
    else
        return {};
}
