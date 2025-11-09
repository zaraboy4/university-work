#include <iostream>
#include <vector>
#include <functional>
#include <list>

template <class Container>
typename Container::iterator longestSeq(const typename Container::iterator& it_begin,
                                                const typename Container::iterator& it_end,
                                                    std::function<bool(int)>&& pred) {
    typename Container::iterator res;
    typename Container::iterator startSeqIterator;
    unsigned int cnt = 0;
    unsigned int max = 0;
    for (auto it = it_begin; it != it_end; ++it) {
        cnt = 0;
        startSeqIterator = it;
        while (it != it_end && pred(*it)) {
            ++cnt;
            ++it;
        }
        if (cnt > max) {
            max = cnt;
            res = startSeqIterator;
        }
        if (it == it_end) break;
    }
    if (max > 0) return res;
    return it_end;
}

int main() {
    std::vector<int> xs { 1, 2, 4, 6, 9, 10, 14, 18 };
    std::cout << *(longestSeq<std::vector<int>>(xs.begin(), xs.end(), [](int x) { return x % 2 == 0; }));
    std::list<int> ls { 1, 2, 4, 6, 9, 11, 10, 14, 18, 17, 19, 21 };
    std::cout << *(longestSeq<std::list<int>>(ls.begin(), ls.end(), [](int x) { return x % 2 == 1; }));
    return 0;
}