#include <iostream>

template <class T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T& d = T(), ListNode* n = nullptr)
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

template <class T>
void print(ListNode<T>* head) {
    while (head) {
        std::cout << head->data;
        if (head->next) std::cout << "->";
        head = head->next;
    }
    std::cout << '\n';
}

template <class T>
void pushBack(ListNode<T>*& head, ListNode<T>*& tail, ListNode<T>* node) {
    if (!head && !tail) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = tail->next;
    }
}

template <class T>
ListNode<T>* mergeSorted(ListNode<T>*& l, ListNode<T>*& r) {
    ListNode<T>* left = l;
    ListNode<T>* right = r;
    ListNode<T>* head = nullptr;
    ListNode<T>* tail = nullptr;
    while (left && right) {
        if (left->data <= right->data) {
            pushBack(head, tail, left);
            left = left->next;
        }
        else {
            pushBack(head, tail, right);
            right = right->next;
        }
    }
    while (left) {
        pushBack(head, tail, left);
        left = left->next;
    }
    while (right) {
        pushBack(head, tail, right);
        right = right->next;
    }
    l = r = nullptr;
    return head;
}

ListNode<int>* deserialize(std::istream& is) {
    ListNode<int>* head = nullptr;
    int size, num;
    is >> size;
    if (!size) return head;
    is >> num;
    ListNode<int>* it = head = new ListNode<int>(num);
    for (int i = 1; i < size; ++i) {
        is >> num;
        it->next = new ListNode<int>(num);
        it = it->next;
    }
    return head;
}

int main() {
    ListNode<int>* xs = deserialize(std::cin);
    ListNode<int>* ys = deserialize(std::cin);

    // ListNode<int>* xs = new ListNode<int>(1, new ListNode<int>(3, new ListNode<int>(5, new ListNode<int>(8))));
    // ListNode<int>* ys = new ListNode<int>(2, new ListNode<int>(2, new ListNode<int>(4)));
    ListNode<int>* ms = mergeSorted(xs, ys);
    print(ms);
    destruct(ms);
    return 0;
}