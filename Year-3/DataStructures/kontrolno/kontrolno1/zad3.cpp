#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr)
        : data(d), next(n) {}
};

void destruct(Node*& head) {
    Node* toDel;
    while (head) {
        toDel = head;
        head = head->next;
        delete toDel;
    }
}

void print(Node* head) {
    while (head) {
        std::cout << head->data;
        if (head->next)
            std::cout << "->";
        head = head->next;
    }
    std::cout << '\n';
}

void pushBack(Node*& head, Node*& tail, Node* node) {
    if (!head && !tail) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = tail->next;
    }
}

Node* rearrange(Node*& head) {
    Node* it = head;
    Node* headRemOne = nullptr;
    Node* tailRemOne = nullptr;
    Node* headRemTwo = nullptr;
    Node* tailRemTwo = nullptr;
    Node* toDel;
    while (it) {
        if (it->data % 3 == 1) {
            pushBack(headRemOne, tailRemOne, it);
        }
        else if (it->data % 3 == 2) {
            pushBack(headRemTwo, tailRemTwo, it);
        }
        else {
            toDel = it;
            it = it->next;
            delete toDel;
            continue;
        }
        it = it->next;
    }
    head = nullptr;
    if (!tailRemOne) {
        headRemOne = headRemTwo;
    }
    else {
        tailRemOne->next = headRemTwo;
    }
    return headRemOne;
}

int main() {
    // Node* head = new Node(0, new Node(1, new Node(2, 
    //                 new Node(3, new Node(4, new Node(5, new Node(6)))))));
    Node* head = new Node(2, new Node(1, new Node(7, new Node(4))));
    print(head);
    Node* res = rearrange(head);
    print(res);
    destruct(res);
    return 0;
}