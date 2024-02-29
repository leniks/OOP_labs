#pragma once

#include <iterator>
#include <memory>

template <class Node, class T>
class Iterator{
private:
    Node* node;

public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    Iterator() = default;
    Iterator(Node* ptr) : node(ptr) {}

    Node* get() const {
        return node;
    }

    reference operator*() const {
        if (node == nullptr) 
            throw std::out_of_range("Iterator dereferences out of bounds");
        return node->data;
    }

    pointer operator->() {
        if (node == nullptr) 
            throw std::out_of_range("Iterator dereferences out of bounds");
        return &node->data;
    }

    Iterator& operator++() {
        if (node == nullptr) 
            throw std::out_of_range("Iterator dereferences out of bounds");
        node = node->next.get();
        return *this;
    }

    Iterator operator++(int) {
        Iterator old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Iterator &other) {
        return node == other.node;
    }

    bool operator!=(const Iterator &other) {
        return node != other.node;
    }

};