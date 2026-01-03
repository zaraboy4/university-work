#ifndef HEADER_DOUBLE_LINKED_LIST_WITH_ITERATOR
#define HEADER_DOUBLE_LINKED_LIST_WITH_ITERATOR

#include <iostream>

template <class T>
class DLList {
public:
    DLList() : head(nullptr), tail(nullptr) {}
    DLList(const DLList& oth) : DLList() { append(oth); }
    DLList(DLList&&);
    DLList& operator=(const DLList&);
    DLList& operator=(DLList&&);
    ~DLList() { erase(); }

    class Iterator;
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    Iterator last() const { return Iterator(tail); }

    bool insertAfter(const Iterator&, const T&);
    bool insertBefore(const Iterator&, const T&);
    bool insertFront(const T& el) { return insertBefore(begin(), el); }
    bool insertBack(const T& el) { return insertAfter(last(), el); }

    bool removeAfter(const Iterator& it) { Iterator n = it.next(); return removeAt(n); }
    bool removeBefore(const Iterator& it) { Iterator p = it.prev(); return removeAt(p); }
    bool removeAt(Iterator&);
    bool removeFirst() { Iterator b = begin(); return removeAt(b); }
    bool removeLast() { Iterator l = last(); return removeAt(l); }

    void append(const DLList<T>& oth);
    void appendAssign();
    void erase();
    bool empty() const { return !head && !tail; }

    void print() const {
        for (const T& x : *this) {
            std::cout << x << ' '; 
        }
        std::cout << '\n';
    }
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d, Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {}
    } *head, *tail;
};

template <class T>
class DLList<T>::Iterator {
    friend DLList<T>;
private:
    Node* ptr;
public:
    Iterator(Node* p = nullptr) : ptr(p) {}
public:
    bool valid() const { return ptr; }
    operator bool() const { return valid(); }
    Iterator next() const {
        if (!valid()) 
            return *this;
        return Iterator(ptr->next);
    }
    Iterator prev() const {
        if (!valid())
            return *this;
        return Iterator(ptr->prev);
    }
    Iterator& operator++() {
        *this = next();
        return *this;
    }
    Iterator& operator--() {
        *this = prev();
        return *this;
    }
    Iterator operator++(int) {
        Iterator saved = *this;
        ++(*this);
        return saved;
    }
    Iterator operator--(int) {
        Iterator saved = *this;
        --(*this);
        return saved;
    }
    Iterator& operator+=(unsigned int n) {
        for (unsigned int i = 0; i < n; ++i) {
            ++(*this);
        }
        return *this;
    }
    Iterator& operator-=(unsigned int n) {
        for (unsigned int i = 0; i < n; ++i) {
            --(*this);
        }
        return *this;
    }
    T& operator*() { return ptr->data; }
    const T& operator*() const { return ptr->data; }
    bool operator==(const Iterator& oth) const { return ptr == oth.ptr; }
    bool operator!=(const Iterator& oth) const { return !(*this == oth); }
};

template <class T>
bool DLList<T>::insertAfter(const Iterator& it, const T& el) {
    if (empty()) {
        head = tail = new Node(el);
        return true;
    }
    if (!it) return false;
    if (!it.next()) {
        it.ptr->next = tail = new Node(el, it.ptr, nullptr);
        return true;
    }
    Node* newEl = new Node(el, it.ptr, it.ptr->next);
    it.ptr->next = newEl;
    newEl->next->prev = newEl;
    return true;
}

template <class T>
bool DLList<T>::insertBefore(const Iterator& it, const T& el) {
    if (empty()) {
        head = tail = new Node(el);
        return true;
    }
    if (!it) return false;
    if (!it.prev()) {
        it.ptr->prev = head = new Node(el, nullptr, it.ptr);
        return true;
    }
    return insertAfter(it.prev(), el);
}

template <class T>
bool DLList<T>::removeAt(Iterator& it) {
    if (empty() || !it)
        return false;
    if (it.prev()) {
        it.ptr->prev->next = it.ptr->next;
    }
    else {
        head = it.ptr->next;
    }
    if (it.next()) {
        it.ptr->next->prev = it.ptr->prev;
    }
    else {
        tail = it.ptr->prev;
    }
    delete it.ptr;
    it.ptr = nullptr;
    return true;
}

template <class T>
void DLList<T>::erase() {
    while (!empty()) {
        removeFirst();
    }
}

template <class T>
void DLList<T>::append(const DLList<T>& oth) {
    for (const T& el : oth) {
        insertBack(el);
    }
}

template <class T>
DLList<T>::DLList(DLList&& oth) {
    head = oth.head;
    tail = oth.tail;
    oth.head = oth.tail = nullptr;
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& oth) {
    if (this != &oth) {
        erase();
        append(oth);
    }
    return *this;
}

template <class T>
DLList<T>& DLList<T>::operator=(DLList<T>&& oth) {
    if (this != &oth) {
        erase();
        head = oth.head;
        tail = oth.tail;
        oth.head = oth.tail = nullptr;
    }
    return *this;
}

#endif