#pragma once
#include <iostream>
//#include <stdexcept>

template <class T>
class Stack {
public:
    Stack() : tos(nullptr) {}
    Stack(const Stack&);
    Stack(Stack&&);
    Stack& operator=(const Stack&);
    Stack& operator=(Stack&&);
    ~Stack() { clear(); }

    void push(const T& el);
    T pop();
    const T& top() const;

    bool isEmpty() const { return !tos; }
private:
    struct Node {
        Node(const T& d = T(), Node* n = nullptr)
            : data(d), next(n) {}
        T data;
        Node* next;
    } *tos;
private:
    void clear();
    void copy(Node*);
};

template <class T>
void Stack<T>::push(const T& el) {
    tos = new Node(el, tos);
}

template <class T>
T Stack<T>::pop() {
    if (isEmpty())
        throw std::underflow_error("empty stack");
    T res = tos->data;
    Node* temp = tos;
    tos = tos->next;
    delete temp;
    //std::cout << "delete node in pop\n";
    return res;
}

template <class T>
const T& Stack<T>::top() const {
    if (isEmpty())
        throw std::underflow_error("empty stack");
    return tos->data;
}

template <class T>
Stack<T>::Stack(const Stack& rhs) {
    //std::cout << "copy contructor\n";
    try {
        copy(rhs.tos);
    }
    catch(...) {
        clear();
        throw;
    }   
}

template <class T>
Stack<T>::Stack(Stack&& rhs) : Stack() { 
    //std::cout << "move copy contructor\n";
    std::swap(tos, rhs.tos); 
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) {
    //std::cout << "assignment operator\n";
    if (this != &rhs) {
        *this = Stack(rhs);
    }
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& rhs) {
    //std::cout << "move assignment operator\n";
    if (this != &rhs) {
        std::swap(tos, rhs.tos);
    }
    return *this;
}

template <class T>
void Stack<T>::clear() {
    Node* temp;
    while (tos) {
        temp = tos;
        tos = tos->next;
        delete temp;
        //std::cout << "delete node in clear()\n";
    }
}

template <class T>
void Stack<T>::copy(Node* rhs_tos) {
    if (!rhs_tos) {
        tos = nullptr;
        return;
    }
    tos = new Node(rhs_tos->data);
    Node* it = tos;
    rhs_tos = rhs_tos->next;
    while (rhs_tos) {
        it->next = new Node(rhs_tos->data);
        it = it->next;
        rhs_tos = rhs_tos->next;
    }
}