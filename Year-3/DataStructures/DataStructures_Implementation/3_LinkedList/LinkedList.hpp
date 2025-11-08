#ifndef _HEADER_LINKED_LIST
#define _HEADER_LINKED_LIST

#include <iostream>

template <class T>
class List {
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    List(const List& src) { copy(src); }
    List(List&&);
    List& operator=(const List&);
    List& operator=(List&&);
    ~List() { del(); }

    bool empty() const { return !head; }
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr)
            : data(d), next(n) {}
    } *head, *tail;
    size_t size;
private:
    void copy(const List&);
    void del();
};

template <class T>
List<T>::List(List&& src) : List() {
    std::swap(head, src.head);
    std::swap(tail, src.tail);
    std::swap(size, src.size);
}

template <class T>
List<T>& List<T>::operator=(const List& src) {
    if (this != &src) {
        del();
        copy(src);
    }
    return *this;
}

template <class T>
List<T>& List<T>::operator=(List&& src) {
    if (this != &src) {
        std::swap(head, src.head);
        std::swap(tail, src.tail);
        std::swap(size, src.size);
    }
    return *this;
}

template <class T>
void List<T>::copy(const List& src) {
    if (src.empty()) {
        head = tail = nullptr;
        size = 0;
        return;
    }
    head = new Node(src.head->data);
    Node* slow = head;
    Node* fast = src.head->next;
    while (fast) {
        slow->next = new Node(fast->data);
        slow = slow->next;
        fast = fast->next;
    }
    tail = slow;
    size = src.size;
}

template <class T>
void List<T>::del() {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = head;
    size = 0;
}

#endif