#include <stdexcept>

template <class T>
class LinkedStack {
public:
    LinkedStack() : tos(nullptr) {}
    LinkedStack(const LinkedStack& src) { copy(src.tos); }
    LinkedStack(LinkedStack&& src) : tos(src.tos) { src.tos = nullptr; }
    LinkedStack& operator=(const LinkedStack&);
    LinkedStack& operator=(LinkedStack&&);
    ~LinkedStack() { del(); }

    void push(const T&);
    void pop();
    const T& top() const;

    bool empty() const { return !tos; }
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr)
            : data(d), next(n) {}
    } *tos;
private:
    void copy(const Node*);
    void del();
};

template <class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& src) {
    if (this != &src) {
        del();
        copy(src.tos);
    }
    return *this;
}

template <class T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack&& src) {
    if (this != &src) {
        del();
        tos = src.tos;
        src.tos = nullptr;
    }
    return *this;
}

template <class T>
void LinkedStack<T>::push(const T& el) {
    tos = new Node(el, tos);
}

template <class T>
void LinkedStack<T>::pop() {
    if (empty())
        throw std::underflow_error("cannot pop from empty stack");
    Node* toDel = tos;
    tos = tos->next;
    delete toDel;
}

template <class T>
const T& LinkedStack<T>::top() const {
    if (empty())
        throw std::underflow_error("cannot get top element of empty stack");
    return tos->data;
}

template <class T>
void LinkedStack<T>::copy(const Node* src_tos) {
    if (!src_tos) {
        tos = nullptr;
        return;
    }
    Node* it = tos = new Node(src_tos->data);
    src_tos = src_tos->next;
    while (src_tos) {
        it->next = new Node(src_tos->data);
        it = it->next;
        src_tos = src_tos->next;
    }
}

template <class T>
void LinkedStack<T>::del() {
    Node* toDel;
    while (tos) {
        toDel = tos;
        tos = tos->next;
        delete toDel;
    }
}