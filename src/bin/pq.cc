#include <functional> // std::less
#include <utility>    // std::swap
#include <vector>     // std::vector

template <typename T, class Container = std::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
class PriorityQueue
{
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = Container::value_type;
    using size_type = Container::size_type;
    using reference = Container::reference;
    using const_reference = Container::const_reference;

    PriorityQueue() : c(Container()), comp(Compare())
    {
    }

    const_reference top() const
    {
        return c.front();
    }

    bool empty() const
    {
        return c.empty();
    }

    size_type size() const
    {
        return c.size();
    }

    void push(const value_type& v)
    {
        c.push_back(v);
        for (size_type i = c.size() - 1; i != 0 && comp(c[i / 2], c[i]); i /= 2)
        {
            std::swap(c[i], c[i / 2]);
        }
    }

    void pop()
    {
        std::swap(c[0], c[c.size() - 1]);
        c.pop_back();
        siftDown(0, c.size());
    }

protected:
    Container c;
    Compare comp;

private:
    void siftDown(size_type i, size_type n)
    {
        size_type l = 2 * i + 1, r = l + 1, largest = i;
        if (l < n && comp(c[i], c[l]))
        {
            largest = l;
        }
        if (r < n && comp(c[largest], c[r]))
        {
            largest = r;
        }
        if (largest != i)
        {
            std::swap(c[i], c[largest]);
            siftDown(largest, n);
        }
    }
};

#include <fmt/base.h>

int main()
{
    PriorityQueue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(50);
    pq.push(3);
    pq.push(1);
    pq.push(7);
    pq.push(20);
    pq.push(2);
    auto x = [&]()
    {
        fmt::println("top={}; pop", pq.top());
        pq.pop();
    };
    x();
    x();
    x();
    x();
    x();
    x();
}
