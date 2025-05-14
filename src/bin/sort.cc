#include "../sorting/sorting.hh"
#include "fmt/base.h"
#include "fmt/ranges.h"
#include <algorithm>
#include <vector>

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        fmt::println(stderr, "Error: Missing sorting algorithm name.");
        return EXIT_FAILURE;
    }
    const char* strategy_name = argv[1];
    std::optional<algo::sorting::Strategy> strategy =
        algo::sorting::strategy_from(strategy_name);
    if (!strategy.has_value())
    {
        fmt::println(stderr, "Error: Unknown sorting algorithm '{}'.", strategy_name);
        return EXIT_FAILURE;
    }
    std::vector<int> a = std::vector<int>();
    std::ranges::transform(argv + 2, argv + argc, std::back_inserter(a),
                           [](const char* x) { return atoi(x); });
    algo::sorting::sort(a.begin(), a.end(), *strategy);
    fmt::println("[{}]", fmt::join(a.begin(), a.end(), ", "));
}
