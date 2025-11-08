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

    class Iterator;
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(); }

    void pushBack(const T&);

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
class List<T>::Iterator {
private:
    friend class List<T>;
    Node* ptr;
public:
    Iterator(Node* p = nullptr) : ptr(p) {}
    bool valid() const { return ptr; }
    operator bool() const { return valid(); }
    Iterator next() {
        if (!valid()) 
            return *this; 
        else 
            return Iterator(ptr->next);
    }
    Iterator& operator++() { *this = next(); return *this; }
    Iterator operator++(int) {
        Iterator saved = *this;
        ++(*this);
        return saved;
    }
    bool operator==(const Iterator& oth) { return ptr == oth.ptr; }
    bool operator!=(const Iterator& oth) { return !(*this == oth); }
    T& operator*() { return ptr->data; }
    const T& operator*() const { return ptr->data; }
    Iterator& operator+=(unsigned int n) {
        for (int i = 0; i < n; ++i) {
            ++(*this);
        }
        return *this;
    }
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
        std::cout << "delete node\n";
    }
    tail = head;
    size = 0;
}

template <class T>
void List<T>::pushBack(const T& el) {
    Node* toAdd = new Node(el);
    if (empty())
        head = tail = toAdd;
    else {
        tail->next = toAdd;
        tail = tail->next;
    }
    ++size;
}

#endif