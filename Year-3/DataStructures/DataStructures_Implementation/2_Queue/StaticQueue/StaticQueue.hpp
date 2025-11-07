#pragma once
// #include <iostream>
#include <stdexcept>

const int MAX_SIZE = 24;

template <class T>
class StaticQueue {
public:
    StaticQueue() : front(0), back(0), size(0) {}
    StaticQueue(const StaticQueue& src) { copy(src); }
    StaticQueue& operator=(const StaticQueue&);

    void enqueue(const T&);
    void dequeue();
    const T& first() const;
    bool empty() const { return size == 0; }
    bool full() const { return back == MAX_SIZE; }

    // void print() const;
private:
    T elements[MAX_SIZE];
    int front, back, size;
private:
    void copy(const StaticQueue&);
};

template <class T>
StaticQueue<T>& StaticQueue<T>::operator=(const StaticQueue& src) {
    if (this != &src) {
        copy(src);
    }
    return *this;
}

template <class T>
void StaticQueue<T>::copy(const StaticQueue& src) {
    for (int i = 0; i < src.size; ++i) {
        elements[i] = src.elements[i + src.front];
    }
    front = 0;
    back = src.size;
    size = src.size;
}

template <class T>
void StaticQueue<T>::enqueue(const T& el) {
    if (full())
        throw std::overflow_error("cannot push an element in a full queue");
    elements[back++] = el;
    size++;
}

template <class T>
void StaticQueue<T>::dequeue() {
    if (empty())
        throw std::underflow_error("cannot remove an element from an empty queue");
    front++;
    size--;
}

template <class T>
const T& StaticQueue<T>::first() const {
    if (empty())
        throw std::underflow_error("cannot get the first element from an empty queue");
    return elements[front];
}

// template <class T>
// void StaticQueue<T>::print() const {
//     for (int i = front; i < back; ++i) {
//         std::cout << elements[i] << ' ';
//     }
//     std::cout << '\n';
// }
