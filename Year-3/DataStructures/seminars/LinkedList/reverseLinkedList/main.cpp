#include <iostream>

template <class T>
struct Node {
    T data;
    Node* next;
    Node(const T& d, Node* n = nullptr)
        : data(d), next(n) {}
};

template <class T>
void destruct(Node<T> *& head) {
    Node<T>* toDel;
    while (head) {
        toDel = head;
        head = head->next;
        delete toDel;
        // std::cout << "delete node\n";
    }
}

template <class T>
void print(const Node<T>* head) {
    while (head) {
        std::cout << head->data;
        if (head->next)
            std::cout << "->";
        head = head->next;
    }
    std::cout << "\n";
}

template <class T>
void reverseList(Node<T>*& head) {
    Node<T>* prev = nullptr;
    Node<T>* nextNode;
    while (head) {
        nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }
    head = prev;
}

template <class T>
Node<T>* middle(Node<T>* head) {
    Node<T> *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <class T>
bool isCycle(Node<T>* head) {
    Node<T> *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

void testMiddle() {
    Node<int>* head_xs = new Node<int>(1,
                            new Node<int>(2, 
                                new Node<int>(3,
                                    new Node<int>(4))));
    print(head_xs);
    std::cout << "middle: " << middle(head_xs)->data << '\n';
    Node<int>* head_ys = new Node<int>(1,
                            new Node<int>(2, 
                                new Node<int>(10,
                                    new Node<int>(4,
                                        new Node<int>(5)))));
    print(head_ys);
    std::cout << "middle: " << middle(head_ys)->data << '\n';
    destruct(head_xs);
    destruct(head_ys);
}

void testReverse() {
    Node<int>* head_xs = new Node<int>(1,
                            new Node<int>(2, 
                                new Node<int>(3,
                                    new Node<int>(4))));
    print(head_xs);
    reverseList(head_xs);
    std::cout << "after reversing: ";
    print(head_xs);
    destruct(head_xs);
}

void testCycleFalse() {
    Node<int>* head_xs = new Node<int>(1,
                            new Node<int>(2, 
                                new Node<int>(3,
                                    new Node<int>(4))));
    print(head_xs);
    std::cout << "is there cycle: " << (isCycle(head_xs) ? "yes" : "no") << '\n';
    destruct(head_xs);
}

template <class T>
void destructSpecific(Node<T> *& head) {
    Node<T>* toDel;
    int i = 0;
    while (i < 4) {
        toDel = head;
        head = head->next;
        delete toDel;
        // std::cout << "delete node\n";
        ++i;
    }
}

void testCycleTrue() {
    Node<int>* head_xs = new Node<int>(1,
                            new Node<int>(2, 
                                new Node<int>(3,
                                    new Node<int>(4))));
    head_xs->next->next->next->next = head_xs;
    // print(head_xs);
    std::cout << "is there cycle: " << (isCycle(head_xs) ? "yes" : "no") << '\n';
    destructSpecific(head_xs);
    // memory leak
}

int main() {
    testMiddle();
    testReverse();
    testCycleTrue();
    return 0;
}