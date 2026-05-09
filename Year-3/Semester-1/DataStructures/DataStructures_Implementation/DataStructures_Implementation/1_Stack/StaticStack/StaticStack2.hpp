#pragma once
#define MAX_CAPACITY 24
#include <stdexcept>

template <class T>
class StaticStack {
public:
    StaticStack() : topIndex(0) {}
    StaticStack(const StaticStack& src) { copy(src); }
    StaticStack& operator=(const StaticStack&);

    void push(const T&);
    T pop();
    const T& peek() const;

    bool empty() const { return topIndex == 0; }
    bool full() const { return topIndex == MAX_CAPACITY; }
private:
    T elements[MAX_CAPACITY];
    int topIndex;
private:
    void copy(const StaticStack&);
};

template <class T>
StaticStack<T>& StaticStack<T>::operator=(const StaticStack& src) {
    if (this != &src) {
        copy(src);
    }
    return *this;
}

template <class T>
void StaticStack<T>::push(const T& el) {
    if (full())
        throw std::overflow_error("full stack");
    elements[topIndex++] = el;
}

template <class T>
T StaticStack<T>::pop() {
    T top = peek();
    topIndex--;
    return top;
}

template <class T>
const T& StaticStack<T>::peek() const {
    if (empty())
        throw std::underflow_error("empty stack");
    return elements[topIndex - 1];
}

template <class T>
void StaticStack<T>::copy(const StaticStack& src) {
    for (int i = 0; i < src.topIndex; ++i) {
        elements[i] = src.elements[i];
    }
    topIndex = src.topIndex;
}