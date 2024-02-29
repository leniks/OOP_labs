#pragma once

#include <functional>
#include "allocator.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

template <class T, class Allocator = std::allocator<T>>
class List {
private:
    struct Node;
    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using NodePointer = std::unique_ptr<Node, std::function<void(Node*)>>;

    struct Node {
        T data;
        NodePointer next;
        Node* prev;
        Node(const T &item) : data(item), next(nullptr), prev(prev) {}
    };

    size_t size;
    NodePointer head;
    Node* tail;

public:
    using iterator = Iterator<Node, T>;
    using const_iterator = ConstIterator<Node, T>;

    List() : size(0), head(nullptr, NodeDelete{nullptr}), tail(nullptr) {}
    iterator begin() {
        return iterator(head.get());
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator cbegin() {
        return const_iterator(head.get());
    }

    const_iterator cend() {
        return const_iterator(nullptr);
    }

    bool isEmpty() {
        return size == 0;
    }

    int Size() {
        return size;
    }

    void PushFront(const T& item) {
        Node* node = allocateNode(item);
        node->next = std::move(head);
        if (head) 
            head->prev = node;
        head = NodePointer(node, NodeDelete{&nodeAllocator});
        if (size == 0)
            tail = head.get();
        ++size;
    }

    void PushBack(const T& item) {
        Node* node = allocateNode(item);
        if (size == 0) {
            head = NodePointer(node, NodeDelete{&nodeAllocator});
            tail = head.get();
        } else {
            tail->next = NodePointer(node, NodeDelete{&nodeAllocator});
            node->prev = tail;
            tail = node;
        }
        ++size;
    }

    void PopFront() {
        if (size == 0)
            throw std::logic_error("Can't pop from empty list");
        head = std::move(head->next);
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        size--;
    }
    void PopBack() {
        if (size == 0)
            throw std::logic_error("Can't pop from empty list");
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } 
        size--;
    }

    T& Head() {
        if (size == 0)
            throw std::logic_error("List is empty");
        return head->data;
    }

    T& Tail() {
        if (size == 0)
            throw std::logic_error("List is empty");
        return tail->data;
    }

    void Insert(iterator pos, const T& item) {
        if (pos == this->begin()) {
            this->PushFront(item);
        } else if (pos == this->end()) {
            this->PushBack(item);
        } else {
            Node* newNode = allocateNode(item);
            Node* prevNode = pos.get()->prev;
            newNode->next = std::move(prevNode->next);
            newNode->prev = prevNode;
            prevNode->next = NodePointer(newNode, NodeDelete{&nodeAllocator});
            newNode->next->prev = newNode;
            size++;
        }
    }
    void Erase(iterator pos) {
        if (pos == this->end())
            throw std::logic_error("Cant't erase end Iterator");
        if (pos == this->begin()) {
            this->PopFront();
            return;
        }
        if (pos.get() == tail) {
            this->PopBack();
            return;
        }

        Node *deletedNode = pos.get();
        if (deletedNode->prev) {
            deletedNode->prev->next = std::move(deletedNode->next);
        } else {
            head = std::move(deletedNode->next);
        }
        if (deletedNode->next) {
            deletedNode->next->prev = deletedNode->prev;
        } else {
            tail = deletedNode->prev;
        }
        size--;
    }

    void Clear() {
        head = nullptr;
        tail = nullptr;
        size = 0;

    }
private:
    NodeAllocator nodeAllocator;

    struct NodeDelete {
        NodeAllocator* allocator;

        void operator()(Node* ptr) const {
            if (ptr != nullptr) {
                std::allocator_traits<NodeAllocator>::destroy(*allocator, ptr);
                allocator->deallocate(ptr, 1);
            }
        }
    };

    Node* allocateNode(const T& item) {
        Node* node = nodeAllocator.allocate(1);
        std::allocator_traits<NodeAllocator>::construct(nodeAllocator, node, item);
        return node;
    }
    
};