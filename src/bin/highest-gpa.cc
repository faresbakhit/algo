#include <fmt/base.h> // namespace fmt
#include <scn/scan.h> // namespace scn

#include <iostream> // std::string
#include <optional> // std::optional
#include <stack>    // std::stack
#include <string>   // std::string

using namespace std;

int main()
{
    std::stack<int> stack;
    int x, y;
    x = 4;
    y = 0;
    stack.push(7);
    stack.push(x);
    stack.push(x + 5);
    y = stack.top();
    stack.pop();
    stack.push(x + y);
    stack.push(y - 2);
    stack.push(3);
    x = stack.top();
    stack.pop();
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    while (!stack.empty())
    {
        cout << stack.top() << endl;
        stack.pop();
    }
}

int _main()
{
    optional<double> highest_gpa;
    stack<string> s;
    while (auto result = scn::input<float, string>("{} {}"))
    {
        if (!result.has_value())
            break;
        auto& [gpa, name] = result->values();
        if (!highest_gpa)
        {
            highest_gpa = gpa;
            s.push(name);
            continue;
        }
        if (gpa > highest_gpa)
        {
            while (!s.empty())
                s.pop();
            highest_gpa = gpa;
        }
        if (gpa >= highest_gpa)
        {
            s.push(name);
        }
    }
    while (!s.empty())
    {
        fmt::println("{}", s.top());
        s.pop();
    }
}