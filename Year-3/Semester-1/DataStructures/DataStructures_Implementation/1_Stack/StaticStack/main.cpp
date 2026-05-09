#include <iostream>
#include <fstream>
#include "./StaticStack2.hpp"

void load(StaticStack<int>& st) {
    std::ifstream ifs("input.txt");
    int size, el;
    ifs >> size;
    for (int i = 0; i < size; ++i) {
        ifs >> el;
        st.push(el);
    }
}

void print(StaticStack<int>& st) {
    while (!st.empty()) {
        std::cout << st.pop() << ' ';
    }
    std::cout << '\n';
}

int main() {
    try {
        StaticStack<int> st;
        load(st);
        // print(st);
        StaticStack<int> cp;
        cp = st;
        print(cp);
    } catch (std::underflow_error& e) {
        std::cout << e.what();
    } catch (std::overflow_error& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "some error occured";
    }
    return 0;
}