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

void infixToPostfix(const string &infixExpr, string& postfixExpr) {
    stack<char> s;
    for (char c : infixExpr) {
        int prec = precedence(c);
        if (prec != -1) {
            postfixExpr.push_back(' ');
            while (!s.empty() && precedence(s.top()) > prec) {
                postfixExpr.push_back(s.top());
                postfixExpr.push_back(' ');
                s.pop();
            }
            s.push(c);
        } else {
            postfixExpr.push_back(c);
        }
    }
    while (!s.empty()) {
        postfixExpr.push_back(s.top());
        s.pop();
    }
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
    infixToPostfix(infixExpr, postfixExpr);
    fmt::println("{}", postfixExpr);
    fmt::println("{}", postfixToAnswer(postfixExpr));
}
