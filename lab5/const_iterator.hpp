#pragma once

#include <iterator>
#include <memory>

template <class Node, class T>
class ConstIterator{
private:
    const Node* node;

public:
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;
    using difference = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    ConstIterator() = default;
    ConstIterator(Node* ptr) : node(ptr) {}

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

    ConstIterator& operator++(int) {
        if (node == nullptr) 
            throw std::out_of_range("Iterator dereferences out of bounds");
        node = node->next.get();
        return *this;
    }

    ConstIterator operator++() {
        ConstIterator old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const ConstIterator &other) {
        return node == other.node;
    }
    
    bool operator!=(const ConstIterator &other) {
        return node != other.node;
    }

};