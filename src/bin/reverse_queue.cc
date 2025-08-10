#include <cassert>
#include <fmt/base.h>
#include <fmt/ranges.h>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
void Reverse(queue<T>& q)
{
    stack<T> s;
    while (!q.empty())
    {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

template <typename T>
void Reverse(stack<T>& s)
{
    queue<T> h;
    while (!s.empty())
    {
        h.push(s.top());
        s.pop();
    }
    while (!h.empty())
    {
        s.push(h.front());
        h.pop();
    }
}

int main()
{
    queue<int> q;
    q.push(5);
    q.push(64);
    q.push(3);
    q.push(10);
    q.push(463);
    Reverse(q);
    while (!q.empty())
    {
        fmt::println("{}", q.front());
        q.pop();
    }
}
