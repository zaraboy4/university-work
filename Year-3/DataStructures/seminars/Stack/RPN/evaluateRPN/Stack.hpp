#include <stdexcept>
#include <iostream>

template <class T>
struct StackNode {
    T data;
    StackNode* next;
    StackNode(const T& d, StackNode* n = nullptr) 
        : data(d), next(n) {}
};

template <class T>
void destruct(StackNode<T>*& tos) {
    StackNode<T>* temp;
    while (tos) {
        temp = tos;
        tos = tos->next;
        delete temp;
        std::cout << "delete node\n";
    }
}

template <class T>
void push(StackNode<T>*& tos, const T& el) {
    tos = new StackNode<T>(el, tos);
}

template <class T>
T pop(StackNode<T>*& tos) {
    T topElement = top(tos);
    StackNode<T>* temp = tos;
    tos = tos->next;
    delete temp;
    return topElement;
}

template <class T>
const T& top(StackNode<T>* tos) {
    if (empty(tos))
        throw std::underflow_error("empty stack");
    return tos->data;
}

template <class T>
bool empty(StackNode<T>* tos) { 
    return !tos; 
}