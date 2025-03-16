#pragma once

#include <ostream> // std::ostream
#include <utility> // std::swap

namespace algo {
namespace detail {
template <typename T>
concept Streamable = requires(std::ostream &os, T value) {
    { os << value } -> std::convertible_to<std::ostream &>;
};
}

template <typename T>
class CircularSinglyLinkedList {
protected:
    struct Node {
        T data;
        Node *next;
    } *head;

public:
    CircularSinglyLinkedList() : head(nullptr) {}

    CircularSinglyLinkedList(const CircularSinglyLinkedList<T> &list) {
        if (list.head == nullptr) {
            return;
        }
        head = new Node{list.head->data, nullptr};
        Node *curr = head;
        Node *currList = list.head->next;
        while (currList != list.head) {
            Node *newNode = new Node{currList->data, nullptr};
            curr = curr->next = newNode;
            currList = currList->next;
        }
        curr->next = head;
    }

    ~CircularSinglyLinkedList() {
        if (head == nullptr) {
            return;
        }
        Node *curr = head, *temp;
        do {
            temp = curr->next;
            delete curr;
            curr = temp;
        } while (curr != head);
    }

    CircularSinglyLinkedList<T> &operator=(const CircularSinglyLinkedList<T> &list) {
        CircularSinglyLinkedList<T> copy(list);
        std::swap(this->head, copy.head);
        return *this;
    }

    CircularSinglyLinkedList(CircularSinglyLinkedList<T> &&list) : head{list.head} {
        list.head = nullptr;
    }

    CircularSinglyLinkedList<T> &operator=(CircularSinglyLinkedList<T> &&list) {
        std::swap(this->head, list.head);
        return *this;
    }

    void push_front(const T &val) {
        Node *newHead = new Node{val, nullptr};
        if (head == nullptr) {
            newHead->next = newHead;
            head = newHead;
            return;
        }
        Node *last = tail();
        last->next = newHead;
        newHead->next = head;
        head = newHead;
    }

    void push_back(const T &val) {
        push_front(val);
        head = head->next;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node *last = tail();
        Node *newHead = (head == head->next ? nullptr : head->next);
        last->next = newHead;
        delete head;
        head = newHead;
    }

    void pop_back() {
        if (head == nullptr) {
            return;
        }
        if (head == head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node *last = head, *lastPrev = head;
        while (last->next != head) {
            lastPrev = last;
            last = last->next;
        }
        lastPrev->next = head;
        delete last;
    }

    bool erase(const T &val) {
        if (head == nullptr) {
            return false;
        }
        if (head->data == val) {
            Node *last = tail();
            Node *newHead = (head == head->next ? nullptr : head->next);
            last->next = newHead;
            delete head;
            head = newHead;
            return true;
        }
        Node *node = head, *nodePrev = head;
        do {
            if (node->data == val) {
                nodePrev->next = node->next;
                delete node;
                return true;
            }
            nodePrev = node;
            node = node->next;
        } while (node != head);
        return false;
    }

    T &back() {
        return tail()->data;
    }
    const T &back() const {
        return tail()->data;
    }

    T &front() {
        return head->data;
    }
    const T &front() const {
        return head->data;
    }

    template <class Tp>
    requires detail::Streamable<Tp>
    friend std::ostream &operator<<(std::ostream &os, const CircularSinglyLinkedList<Tp> &list);

private:
    Node *tail() {
        Node *last = head;
        while (last->next != head) {
            last = last->next;
        }
        return last;
    }
};

template <class T>
requires detail::Streamable<T>
std::ostream &operator<<(std::ostream &os, const CircularSinglyLinkedList<T> &list) {
    if (list.head == nullptr) {
        return os;
    }
    typename CircularSinglyLinkedList<T>::Node *curr = list.head;
    do {
        os << curr->data << " → ";
        curr = curr->next;
    } while (curr != list.head);
    os << "(back to head)";
    return os;
}
} // namespace algo
