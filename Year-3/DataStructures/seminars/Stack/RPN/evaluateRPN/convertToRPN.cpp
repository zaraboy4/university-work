#include "./Stack.hpp"
#include <iostream>
#include <string.h>

bool isDigit(const char ch) { return '0' <= ch && ch <= '9'; }

bool isOperator(const char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }

int getPriority(const char ch) {
    if (ch == '(') return 0;
    if (ch == '+' || ch == '-') return 10;
    return 20;
}

const char* convertToRPN(const char* str) {
    char* result = new char[255];
    int index = 0;
    StackNode<char>* operators = nullptr;
    while (*str != '\0') {
        if (*str == ' ') { ; }
        else if (isDigit(*str)) {
            result[index++] = *str;
            if (!isDigit(*(str + 1))) {
                result[index++] = ' ';
            }       
        }
        else if (*str == '(') {
            push(operators, *str);
        }
        else if (isOperator(*str)) {
            while (!empty(operators) && getPriority(*str) <= getPriority(top(operators))) {
                result[index++] = pop(operators);
                result[index++] = ' ';
            }
            push(operators, *str);
        }
        else if (*str == ')') {
            while (!empty(operators) && top(operators) != '(') {
                result[index++] = pop(operators);
                result[index++] = ' ';
            }
            if (empty(operators)) {
                delete result;
                throw std::logic_error("bad expression: opening bracket not found");
            }
            pop(operators);
        }
        else {
            destruct(operators);
            delete result;
            throw std::invalid_argument("unknown character");
        }
        ++str;
    }
    while (!empty(operators)) {
        result[index++] = pop(operators);
        result[index++] = ' '; 
    }
    result[index] = '\0';
    return result;
}

int main() {
    char str[255];
    std::cin.getline(str, 255);
    while (*str != 'q') {
        const char* res;
        try {
            res = convertToRPN(str);
            std::cout << "result: " << res << '\n';
            delete res;
        } catch (const std::logic_error& e) {
            std::cout << e.what() << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << '\n';
        }
        std::cin.getline(str, 255);
    }
}