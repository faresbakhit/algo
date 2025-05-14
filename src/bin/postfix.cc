#include <cctype>
#include <iostream>
#include <optional>
#include <sstream>
#include <stack>
#include <string>

#include "fmt/base.h"
#include "fmt/ostream.h"

#define BOOST_MP_STANDALONE
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace boost::multiprecision;

template <>
struct fmt::formatter<cpp_int> : fmt::ostream_formatter {};

int precedence(char op) {
    if (op == '+' || op == '-')
        return 0;
    if (op == '*' || op == '/')
        return 1;
    return -1;
}

cpp_int eval(char op, cpp_int a, cpp_int b) {
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    return -1;
}

string infixToPostfix(const string &infixExpr) {
    ostringstream oss;
    stack<char> s;
    for (char c : infixExpr) {
        if (precedence(c) != -1) {
            oss << ' ';
            while (!s.empty() && precedence(s.top()) > precedence(c)) {
                oss << s.top();
                s.pop();
            }
            s.push(c);
        } else {
            oss << c;
        }
    }
    while (!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

cpp_int postfixToAnswer(const string &postfixExpr) {
    stack<cpp_int> s;
    optional<cpp_int> x;
    for (auto it = postfixExpr.cbegin(); it != postfixExpr.cend(); it++) {
        if (isdigit(*it)) {
            if (x.has_value()) {
                *x *= 10;
                *x += *it - '0';
            } else {
                x = *it - '0';
            }
        } else if (x.has_value()) {
            s.push(*x);
            x.reset();
        }
        if (precedence(*it) != -1) {
            cpp_int a = s.top();
            s.pop();
            cpp_int b = s.top();
            s.pop();
            s.push(eval(*it, b, a));
        }
    }
    return s.top();
}

int main() {
    std::string infixExpr, postfixExpr;
    getline(cin, infixExpr);
    postfixExpr = infixToPostfix(infixExpr);
    fmt::println("{}", postfixExpr);
    fmt::println("{}", postfixToAnswer(postfixExpr));
}
