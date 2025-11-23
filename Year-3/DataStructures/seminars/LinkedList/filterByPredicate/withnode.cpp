#include <iostream>

template <class T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T& d, ListNode* n = nullptr)
        : data(d), next(n) {}
};

template <class T>
void destruct(ListNode<T>*& head) {
    ListNode<T>* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <class T, class Pred>
void filter(ListNode<T>*& head, const Pred& pr) {
    if (!head) return;
    ListNode<T>* it = head;
    while (it) {
        if (pr(it->data)) {
            
        }
    }
}

int main() {

    return 0;
}