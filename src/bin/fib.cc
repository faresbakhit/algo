#define BOOST_MP_STANDALONE
#include "boost/multiprecision/cpp_int.hpp"
#include "fmt/base.h"
#include "fmt/ostream.h"

using namespace boost::multiprecision;

template <>
struct fmt::formatter<cpp_int> : fmt::ostream_formatter {};

cpp_int recursiveFib(cpp_int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 1;
    return recursiveFib(n - 1) + recursiveFib(n - 2);
}

cpp_int iterativeFib(cpp_int n) {
    if (n < 2)
        return 1;
    cpp_int a = 1;
    cpp_int b = 1;
    for (cpp_int i = 2; i <= n; i++) {
        cpp_int x = a + b;
        a = b;
        b = x;
    }
    return b;
}

int main() {
    for (int i = 0; i < 100; i++) {
        fmt::println("iterativeFib({}): {}", i, iterativeFib(i));
    }
}