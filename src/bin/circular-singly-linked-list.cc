/**
 * @file circular-singly-linked-list.cc
 * @brief Implementation of a circular singly linked list in C++.
 * @author Fares A. Bakhit
 * @date March 16, 2025
 */

#include "../linked_list/circular_singly_linked_list.hh"
#include <iostream>

int main() {
    algo::CircularSinglyLinkedList<int> list1;
    list1.push_back(54);
    list1.push_back(30);
    list1.push_back(10);
    list1.push_front(90);
    list1.push_back(100);
    std::cout << list1 << "\n";
    list1.pop_front();
    list1.pop_front();
    std::cout << list1 << "\n";
    list1.pop_back();
    std::cout << list1 << "\n";
}
