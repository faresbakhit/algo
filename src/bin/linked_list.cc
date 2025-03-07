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

    DoublyLinkedList<int> z1;
    z1.pushBack(3);
    z1.pushFront(1);
    z1.pushBack(2);
    z1.erase(std::next(z1.begin(), 2));
    z1.erase(z1.begin());
    z1.pushBack(1);
    z1.pushBack(0);
    fmt::println("[{}] (front={}, back={})", fmt::join(z1.begin(), z1.end(), ", "), z1.front(), z1.back());

    DoublyLinkedList<int> z2;
    z2.pushBack(10);
    z2.pushBack(20);
    z2.pushBack(30);
    fmt::println("[{}] (front={}, back={})", fmt::join(z2.begin(), z2.end(), ", "), z2.front(), z2.back());
    z1.splice(std::next(z1.begin(), 2), z2);
    fmt::println("[{}] (front={}, back={})", fmt::join(z1.begin(), z1.end(), ", "), z1.front(), z1.back());
    fmt::println("[{}]", fmt::join(z2.begin(), z2.end(), ", "));

    UnorderedLinkedList<int> w;
    w.pushBack(3);
    w.pushBack(6);
    w.pushBack(9);
    std::next(w.begin(), 2).node->next = w.begin().node;
    fmt::println("{}", w.trace());
}
