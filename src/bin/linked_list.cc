#include "../linked_list/linked_list.hh"
#include <cassert>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

using namespace algo;

template <class T, class Node>
struct fmt::formatter<LinkedListTrace<T, Node>> : fmt::ostream_formatter {};

int main() {
    UnorderedLinkedList<int> x;
    x.pushBack(5);
    x.pushFront(7);
    x.pushBack(1);
    x.pushBack(9);
    *std::next(x.begin(), 2) += 2;
    fmt::println("[{}] (front={}, back={})", fmt::join(x.begin(), x.end(), ", "), x.front(), x.back());
    assert(std::next(x.begin(), 4) == x.end());

    OrderedLinkedList<int> y;
    y.insert(1);
    y.insert(6);
    y.insert(9);
    y.insert(0);
    y.insert(3);
    y.insert(7);
    y.insert(11);
    fmt::println("[{}] (front={}, back={})", fmt::join(y.begin(), y.end(), ", "), y.front(), y.back());

    DoublyLinkedList<int> z;
    z.pushBack(3);
    z.pushFront(1);
    z.pushBack(2);
    z.erase(std::next(z.begin(), 2));
    z.erase(z.begin());
    z.pushBack(1);
    fmt::println("[{}] (front={}, back={})", fmt::join(z.begin(), z.end(), ", "), z.front(), z.back());

    UnorderedLinkedList<int> w;
    w.pushBack(3);
    w.pushBack(6);
    w.pushBack(9);
    std::next(w.begin(), 2).node->next = w.begin().node;
    fmt::println("{}", w.trace());
}
