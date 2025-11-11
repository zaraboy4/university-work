#include "D:/uni/kurs3/sdp/DataStructures_Implementation/1_Stack/StaticStack/StaticStack.hpp"

#include <iostream>
#include <fstream>

bool isOperator(const char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isDigit(const char ch) { return '0' <= ch && ch <= '9'; }

int getNum(const char*& str) {
    int num = 0;
    while (isDigit(*str)) {
        num = num * 10 + *str - '0';
        ++str;
    }
    --str; 
    return num;
}

void apply(StaticStack<int>& numbers, const char op) {
    if (numbers.empty())
        throw std::logic_error("missing operand for operation");
    int right = numbers.pop();
    if (numbers.empty())
        throw std::logic_error("missing operand for operation");
    int left = numbers.pop();
    int res = 0;
    switch (op) {
        case '+': res = left + right; break;
        case '-': res = left - right; break;
        case '/': res = left / right; break;
        case '*': res = left * right; break;
        default: break;
    }
    numbers.push(res);
}

int evalRPN(const char* str) {
    StaticStack<int> numbers;
    while (*str != '\0') {
        if (*str == ' ') { ; }
        else if (isDigit(*str)) {
            numbers.push(getNum(str));
        }
        else if (isOperator(*str)) {
            if (*str == '-') {
                if (isDigit(*(str + 1))) {
                    numbers.push(-1 * getNum(++str));
                }
                else apply(numbers, '-');
            }
            else apply(numbers, *str);
        }
        else throw std::invalid_argument("unknown character");
        ++str;
    }
    if (numbers.empty())
        throw std::logic_error("bad rpn expression");
    int res = numbers.pop();
    if (!numbers.empty())
        throw std::logic_error("bad rpn expression");
    return res;
}

int main() {
    try {
        // std::ifstream ifs("rpn_tests.txt");
        // char str[255]; int res;
        // while (ifs.getline(str, 255)) {
        //     ifs >> res;
        //     if (res == evalRPN(str)) {
        //         std::cout << "true: " << str << " <-> " << res << '\n';
        //     }
        //     else {
        //         std::cout << "false: " << str << " <-> " << res << '\n';
        //     }
        //     ifs.getline(str, 255);
        // }
        char str[255];
        std::cin.getline(str, 255);
        std::cout << "result: " << evalRPN(str) << '\n';
    } catch (std::logic_error& e) {
        std::cout << e.what();
    } catch (std::invalid_argument& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "some error occurred";
    }
    return 0;
}