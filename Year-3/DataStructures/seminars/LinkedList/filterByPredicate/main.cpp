#include <forward_list>
#include <functional>
#include <iostream>


template <class Predicate>
void filter(std::forward_list<int>& xs, const Predicate& pred) {
    if (xs.empty()) return;
    std::forward_list<int>::iterator it = xs.begin();
    std::forward_list<int>::iterator it_next = ++it;
    while (it != xs.end() && it_next != xs.end()) {
        if (pred(*it_next)) {
            xs.erase_after(it);
        }
        ++it;
        ++it_next;
    }
}

bool func(int x) {
    return x > 3;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    std::forward_list<int> xs;
    xs.push_front(arr[0]);
    std::forward_list<int>::iterator it = xs.begin();
    for (int i = 1; i < 7; ++i) {
        xs.insert_after(it, arr[i]);
        ++it;
    }
    filter(xs, func);
    for (auto x : xs) {
        std::cout << x << ' '; 
    } std::cout << "\n";
    return 0;
}