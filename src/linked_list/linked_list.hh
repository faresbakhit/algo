#pragma once

#include "circular_singly_linked_list.hh" // algo::detail::Streamable
#include <cstddef>                        // std::size_t
#include <functional>                     // std::less
#include <ostream>                        // std::ostream

namespace algo {
namespace detail {
template <class T>
struct LinkedListNode {
    T data;
    LinkedListNode<T> *next;

    LinkedListNode() : data(), next(nullptr) {}
    LinkedListNode(const T &value) : data(value), next(nullptr) {}
    LinkedListNode(const T &value, LinkedListNode<T> *link) : data(value), next(link) {}
};

template <class T>
struct DoublyLinkedListNode {
    T data;
    DoublyLinkedListNode<T> *next;
    DoublyLinkedListNode<T> *prev;

    DoublyLinkedListNode() : data(), next(nullptr), prev(nullptr) {}
    DoublyLinkedListNode(const T &value) : data(value), next(nullptr), prev(nullptr) {}
    DoublyLinkedListNode(const T &value, DoublyLinkedListNode<T> *nextLink)
        : data(value), next(nextLink), prev(nullptr) {}
    DoublyLinkedListNode(const T &value, DoublyLinkedListNode<T> *nextLink, DoublyLinkedListNode<T> *prevLink)
        : data(value), next(nextLink), prev(prevLink) {}
};
} // namespace detail

template <class T, class Node>
class LinkedListTrace {
public:
    LinkedListTrace(const Node *linkedListNode) : node(linkedListNode) {}

    template <class Tp, class NodeP>
    requires detail::Streamable<Tp>
    friend std::ostream &operator<<(std::ostream &os, const LinkedListTrace<Tp, NodeP> &linkedListTrace);

    template <class Tp, class NodeP>
    friend std::ostream &operator<<(std::ostream &os, const LinkedListTrace<Tp, NodeP> &linkedListTrace);

private:
    const Node *node;
};

template <class T, class Node>
requires detail::Streamable<T>
std::ostream &operator<<(std::ostream &os, const LinkedListTrace<T, Node> &linkedListTrace) {
    const Node *node = linkedListTrace.node;
    const Node *next = node->next, *nextFast = next == nullptr ? nullptr : next->next;
    if (next != nullptr)
        os << "  ";
    os << (void *)(node) << " [" << node->data << "]";
    while (next != nullptr) {
        os << "\n→ " << (void *)(next) << " [" << next->data << "]";
        next = next->next;
        if (nextFast != nullptr && nextFast->next != nullptr) {
            nextFast = nextFast->next->next;
            if (next == nextFast) {
                os << "\n→ " << (void *)(next) << " [" << next->data << "]";
                next = node;
                while (next != nextFast) {
                    next = next->next;
                    nextFast = nextFast->next;
                }
                os << "\n→ ... (loop at " << (void *)next << " [" << next->data << "])";
                return os;
            }
        }
    }
    return os;
}

template <class T, class Node>
std::ostream &operator<<(std::ostream &os, const LinkedListTrace<T, Node> &linkedListTrace) {
    const Node *node = linkedListTrace.node;
    const Node *next = node->next, *nextFast = next == nullptr ? nullptr : next->next;
    if (next != nullptr)
        os << "  ";
    os << (void *)(node);
    while (next != nullptr) {
        os << "\n→ " << (void *)(next);
        next = next->next;
        if (nextFast != nullptr && nextFast->next != nullptr) {
            nextFast = nextFast->next->next;
            if (next == nextFast) {
                os << "\n→ " << (void *)(next);
                next = node;
                while (next != nextFast) {
                    next = next->next;
                    nextFast = nextFast->next;
                }
                os << "\n→ ... (loop at " << (void *)next << ")";
                return os;
            }
        }
    }
    return os;
}

template <class T, class Node>
class LinkedListIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;

    LinkedListIterator() : node(nullptr) {}
    LinkedListIterator(Node *node) : node(node) {}

    T &operator*() const {
        return node->data;
    }

    LinkedListIterator<T, Node> &operator++() {
        node = node->next;
        return *this;
    }

    LinkedListIterator<T, Node> operator++(int) {
        LinkedListIterator<T, Node> x = *this;
        node = node->next;
        return x;
    }

    bool operator==(const LinkedListIterator<T, Node> &other) const {
        return node == other.node;
    }

    Node *node;
};

template <class T, class Node>
class LinkedList {
public:
    LinkedList() : count(0), first(nullptr), last(nullptr) {}

    ~LinkedList() {
        clear();
    }

    T &back() {
        return last->data;
    }
    const T &back() const {
        return last->data;
    }

    T &front() {
        return first->data;
    }
    const T &front() const {
        return first->data;
    }

    virtual void pushBack(const T &value) {
        Node *newLast = new Node(value);
        if (first == nullptr)
            first = newLast;
        else
            last->next = newLast;
        last = newLast;
        count++;
    }

    virtual void pushFront(const T &value) {
        Node *newFirst = new Node(value, first);
        if (first == nullptr)
            last = newFirst;
        first = newFirst;
        count++;
    }

    virtual void erase(const LinkedListIterator<T, Node> &pos) {
        Node *prev = nullptr;
        Node *curr = first;
        while (curr != nullptr) {
            if (curr == pos.node) {
                if (prev == nullptr) {
                    first = curr->next;
                } else {
                    prev->next = curr->next;
                }
                if (curr == last)
                    last = prev;
                count--;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void clear() {
        Node *temp;
        while (first != nullptr && first != last /* circular lists */) {
            temp = first->next;
            delete first;
            first = temp;
        }
        delete last;
        last = nullptr;
        count = 0;
    }

    std::size_t size() {
        return count;
    }

    bool empty() {
        return first == nullptr;
    }

    LinkedListIterator<T, Node> begin() {
        return LinkedListIterator<T, Node>(first);
    }

    LinkedListIterator<T, Node> end() {
        return LinkedListIterator<T, Node>(nullptr);
    }

    LinkedListTrace<T, Node> trace() {
        return LinkedListTrace<T, Node>(first);
    }

protected:
    std::size_t count;
    Node *first;
    Node *last;
};

template <class T>
class UnorderedLinkedList : public LinkedList<T, detail::LinkedListNode<T>> {};

template <class T, class Compare = std::less<T>>
class OrderedLinkedList : public LinkedList<T, detail::LinkedListNode<T>> {
    using Node = detail::LinkedListNode<T>;

public:
    OrderedLinkedList(const Compare &comp = Compare()) : LinkedList<T, Node>(), m_comp(comp) {}

    virtual void pushBack(const T &value) override {
        insert(value);
    }

    virtual void pushFront(const T &value) override {
        insert(value);
    }

    void insert(const T &value) {
        Node *prev = nullptr;
        Node *curr = this->first;
        Node *node = new Node(value);
        while (curr != nullptr) {
            if (m_comp(value, curr->data))
                break;
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) {
            node->next = this->first;
            this->first = node;
        } else {
            prev->next = node;
            node->next = curr;
        }
        if (curr == nullptr) {
            if (this->last != nullptr)
                this->last->next = node;
            this->last = node;
        }
    }

private:
    Compare m_comp;
};

template <class T>
class DoublyLinkedList : public LinkedList<T, detail::DoublyLinkedListNode<T>> {
    using Node = detail::DoublyLinkedListNode<T>;

public:
    virtual void pushBack(const T &value) override {
        Node *newLast = new Node(value, nullptr, this->last);
        if (this->first == nullptr)
            this->first = newLast;
        else
            this->last->next = newLast;
        this->last = newLast;
        this->count++;
    }

    virtual void pushFront(const T &value) override {
        Node *newFirst = new Node(value, this->first);
        if (this->first == nullptr)
            this->last = newFirst;
        else
            this->first->prev = newFirst;
        this->first = newFirst;
        this->count++;
    }

    virtual void erase(const LinkedListIterator<T, Node> &pos) override {
        Node *node = pos.node;
        if (node->prev != nullptr)
            node->prev->next = node->next;
        if (node->next != nullptr)
            node->next->prev = node->prev;
        if (node == this->first)
            this->first = node->next;
        if (node == this->last)
            this->last = node->prev;
        delete node;
    }

    void merge(const LinkedListIterator<T, Node> &pos, DoublyLinkedList<T> &other) {
        Node *node = pos.node;

        if (this->first == nullptr) {
            this->first = other.first;
            this->last = other.last;
        } else if (node == nullptr) {
            this->last->next = other.first;
            other.first->prev = this->last;
            this->last = other.last;
        } else if (node == this->first) {
            this->first->prev = other.last;
            other.last->next = this->first;
            this->first = other.first;
        } else {
            node->prev->next = other.first;
            other.first->prev = node->prev;
            node->prev = other.last;
            other.last->next = node;
        }

        this->count += other.count;
        other.first = nullptr;
        other.last = nullptr;
        other.count = 0;
    }
};
} // namespace algo
