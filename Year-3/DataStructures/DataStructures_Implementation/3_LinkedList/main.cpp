#include "./LinkedList.hpp"

int main() {
    List<int> xs;
    for (int i = 0; i < 5; ++i)
        xs.pushBack(i + 1);
    List<int> ys;
    for (int i = 0; i < 7; ++i) {
        ys.pushBack((i + 1) * 2);
    }
    ys = std::move(xs);
    std::cout << "xs: ";
    for (int x : xs) std::cout << x << "->";
    std::cout << "\n";
    std::cout << "ys: ";
    for (int y : ys) std::cout << y << "->";
    std::cout << "\n";
    return 0;
}