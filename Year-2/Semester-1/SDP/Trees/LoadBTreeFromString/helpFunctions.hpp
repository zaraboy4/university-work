#pragma once
#include <stdexcept>

int length(const char* str) {
    int len = 0;
    while (str[len] != 0) ++len;
    return len;
}

bool isSpace(const char ch) {
    return ch == ' ';
}

bool isDigit(const char ch) {
    return ch >= '0' && ch <= '9';
}

bool isOpeningBr(const char ch) {
    return ch == '(';
}

bool isClosingBr(const char ch) {
    return ch == ')';
}

bool isNullptr(const char ch) {
    return ch == 'x';
}

int getNum(const char*& str) {
    int num = 0;
    while (isDigit(*str)) {
        num = num * 10 + *str - '0';
        ++str;
    }
    return num;
}

int getPriority(const char ch) {
    if (ch == '+' || ch == '-') return 1;
    else if (ch == '*' || ch == '/') return 2;
    else return 0;
}