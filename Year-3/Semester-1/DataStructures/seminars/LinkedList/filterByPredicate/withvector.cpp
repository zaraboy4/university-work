#include <iostream>
#include <vector>

template <class Predicate>
void filter(std::vector<int>& xs, const Predicate& pred) {
    for (std::vector<int>::iterator it = xs.begin(); it != xs.end(); ++it) {
        if (pred(*it)) {
            xs.erase(it);
        }
    }
}

int main() {
    std::vector<int> xs = { 1, 2, 3, 4, 5, 6, 7 };
    filter(xs, [](const int& x) { return x % 2 == 0; });
    for (int x : xs) {
        std::cout << x << ' ';
    } std::cout << '\n';
    return 0;
}