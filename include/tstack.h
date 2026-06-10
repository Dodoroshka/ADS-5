// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template<typename T, int size>
class TStack {
 private:
    T arr[size] = {};
    int top;

 public:
    TStack() : top(-1) {}

    void push(T item) {
        if (top < static_cast<int>(size) - 1) {
            arr[++top] = item;
        } else {
            throw std::string("Full");
        }
    }

    T get() const {
        if (top < 0) {
            throw std::string("empty");
        }
        return arr[top];
    }

    void pop() {
        if (top < 0) {
            throw std::string("empty");
        }
        --top;
    }

    bool isEmpty() const {
        return top == -1;
    }

    size_t getSize() const {
        return top + 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
