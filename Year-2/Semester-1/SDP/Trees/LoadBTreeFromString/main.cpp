#include "headers/Stack.hpp"
#include "headers/helpFunctions.hpp"
#include "headers/TreeNode.hpp"

void apply(Stack<Node*>& nodes) {
    if (nodes.isEmpty())
        throw std::logic_error("bad expression");
    Node* r = nodes.pop();
    if (nodes.isEmpty())
        throw std::logic_error("bad expression");
    Node* l = nodes.pop();
    if (nodes.isEmpty())
        throw std::logic_error("bad expression");
    Node* top = nodes.pop();
    top->left = l;
    top->right = r;
    nodes.push(top);
}

Node* strToTree(const char* str) {
    Node* res = nullptr;
    Stack<Node*> nodes;
    Stack<char> brackets;
    while (*str != 0) {
        if (isSpace(*str)) { ++str; }
        else if (isNullptr(*str)) { nodes.push(nullptr); ++str; }
        else if (isDigit(*str)) { nodes.push(new Node(getNum(str))); }
        else if (isOpeningBr(*str)) {
            brackets.push(*str);
            ++str;
        }
        else if (isClosingBr(*str)) {
            if (brackets.isEmpty())
                throw std::logic_error("bad expression");
            if (isOpeningBr(brackets.top())) {
                apply(nodes);
            }
            brackets.pop();
            ++str;
        }
        else throw std::invalid_argument("unknown operator");
    }
    if (!brackets.isEmpty())
        throw std::logic_error("bad expression");
    if (nodes.isEmpty()) 
        throw std::logic_error("bad expression");
    res = nodes.pop();
    if (!nodes.isEmpty()) 
        throw std::logic_error("bad expression");
    return res;
}

int main() {
    char str[255];
    std::cout << "Enter input: ";
    std::cin.getline(str, 255);
    while (*str != 'q') {
        Node* btree = strToTree(str);
        print(btree); std::cout << "\n";
        destruct(btree);
        std::cout << "Enter input: ";
        std::cin.getline(str, 255);
    }
    return 0;
}