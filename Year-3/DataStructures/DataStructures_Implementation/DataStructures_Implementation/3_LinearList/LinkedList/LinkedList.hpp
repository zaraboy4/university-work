#ifndef _HEADER_LINKED_LIST
#define _HEADER_LINKED_LIST

#include <utility>
#include <iostream>

template <class T>
struct Node {
    T data;
    Node* next;
    Node(const T& _data, Node* _next = nullptr) 
        :  data(_data), next(_next) {}
};

template <class T>
class LinkedList;

template <class T>
class Iterator {
    friend class LinkedList<T>;
public:
    Iterator(Node<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr; }
    operator bool() const { return valid(); }
    Iterator next() {
        if (!valid()) return *this;
        return Iterator(ptr->next);
    }
    Iterator& operator++() { *this = next(); return *this; }
    Iterator operator++(int) {
        Iterator saved = *this;
        ++(*this);
        return saved;
    }
    Iterator& operator+=(unsigned int n) {
        for (unsigned int i = 0; i < n; ++i) 
            ++(*this);
        return *this;
    }
    T& operator*() { return ptr->data; }
    const T& operator*() const { return ptr->data; }
    bool operator==(const Iterator& oth) const { return ptr == oth.ptr; }
    bool operator!=(const Iterator& oth) const { return !(*this == oth); }
private:
    Node<T>* ptr;
};

template <class T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    LinkedList(const LinkedList& oth) { copy(oth.head); }
    LinkedList(LinkedList&&);
    LinkedList& operator=(const LinkedList&);
    LinkedList& operator=(LinkedList&&);
    ~LinkedList() { del(); }

    Iterator<T> begin() const { return Iterator<T>(head); }
    Iterator<T> end() const { return Iterator<T>(); }
    Iterator<T> last() const { return Iterator<T>(tail); }

    bool insertAfter(const Iterator<T>&, const T&);
    bool insertBefore(const Iterator<T>&, const T&);
    bool insertBack(const T& el) { return insertAfter(last(), el); }
    bool insertFront(const T& el) { return insertBefore(begin(), el); } 

    bool deleteAfter(const Iterator<T>&);
    bool deleteBefore(const Iterator<T>&);
    bool deleteAt(Iterator<T>&);
    bool deleteBack() { 
        Iterator<T> it = last();
        return deleteAt(it); 
    }
    bool deleteFront() { 
        Iterator<T> it = begin();
        return deleteAt(it); 
    }

    void append(const LinkedList&);
    void appendAssign(LinkedList&&);

    bool empty() const { return !head && !tail; }

    void print() const {
        for (T el : *this)
            std::cout << el << ' ';
        std::cout << "\n";
    }
private:
    Node<T> *head, *tail;
private:
    void copy(const Node<T>*);
    void del();
private:
    Iterator<T> findPrev(const Iterator<T>& it) const;
};

template <class T>
LinkedList<T>::LinkedList(LinkedList&& oth) : LinkedList() {
    std::swap(head, oth.head);
    std::swap(tail, oth.tail);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& oth) {
    if (this != &oth) {
        del();
        copy(oth.head);
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& oth) {
    if (this != &oth) {
        std::swap(head, oth.head);
        std::swap(tail, oth.tail);
    }
    return *this;
}

template <class T>
void LinkedList<T>::copy(const Node<T>* oth_it) {
    if (!oth_it) {
        head = tail = nullptr;
        return;
    }
    head = new Node<T>(oth_it->data);
    Node<T>* slow = head;
    oth_it = oth_it->next;
    while (oth_it) {
        slow->next = new Node<T>(oth_it->data);
        slow = slow->next;
        oth_it = oth_it->next;
    }
    tail = slow;
}

// template <class T>
// void LinkedList<T>::copy(const LinkedList& oth) {
    
// }

template <class T>
void LinkedList<T>::del() {
    Node<T>* toDel;
    while (head) {
        toDel = head;
        head = head->next;
        delete toDel;
    }
}

template <class T>
Iterator<T> LinkedList<T>::findPrev(const Iterator<T>& it) const {
    if (it == begin()) return end();
    if (it == end()) return last();
    Iterator<T> target = begin();
    while (target && target.next() != it)
        ++target;
    return target;
}

template <class T>
bool LinkedList<T>::insertAfter(const Iterator<T>& it, const T& el) {
    if (empty()) {
        head = tail = new Node<T>(el);
        return true;
    }
    it.ptr->next = new Node<T>(el, it.ptr->next);
    if (tail == it.ptr) 
        tail = tail->next;
    return true;
}

template <class T>
bool LinkedList<T>::insertBefore(const Iterator<T>& it, const T& el) {
    if (it == begin()) {
        head = new Node<T>(el, head);
        if (!tail) tail = head;
        return true;
    }
    return insertAfter(findPrev(it), el);
}

template <class T>
bool LinkedList<T>::deleteAfter(const Iterator<T>& it) {
    if (!it) return false;
    Node<T>* toDel = it.ptr->next;
    if (!toDel) return false;
    it.ptr->next = toDel->next;
    if (tail == toDel) {
        tail = it.ptr;
    }
    delete toDel;
    return true;
}

template <class T>
bool LinkedList<T>::deleteBefore(const Iterator<T>& it) {
    if (it == begin()) return false;
    Iterator<T> prev = findPrev(it);
    return deleteAt(prev);
}

template <class T>
bool LinkedList<T>::deleteAt(Iterator<T>& it) {
    if (!it) return false;
    if (it == begin()) {
        Node<T>* toDel = head;
        head = head->next;
        if (toDel == tail) {
            tail = nullptr;
        }
        delete toDel;
        it.ptr = nullptr;
        return true;
    }
    Iterator<T> prev = findPrev(it);
    it.ptr = nullptr;
    return deleteAfter(prev);
}

template <class T>
void LinkedList<T>::append(const LinkedList& oth) {
    for (Iterator<T> it = oth.begin(); it; ++it) {
        T el = *it;
        this->insertBack(el);
    }
}

template <class T>
void LinkedList<T>::appendAssign(LinkedList&& oth) {
    if (empty()) {
        std::swap(head, oth.head);
        std::swap(tail, oth.tail);
    }
    else {
        tail->next = oth.head;
        oth.head = nullptr;
        oth.tail = nullptr;
    }
}

#endif