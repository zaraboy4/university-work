#include <iostream>

#define MAX_SIZE 256

class TinySet {
public:
    bool add(int);
    bool removeIfExists(int);
    bool contains(int) const;

    class iterator {
    private:
        TinySet* set;
        int index;
    public:
        iterator(TinySet* s, int ind) : set(s), index(ind) {}
        int& operator*() const { return set->elements[index]; }
        iterator& operator++() {
            ++index;
            return *this;
        }
        iterator operator++(int) {
            iterator saved = *this;
            ++(*this);
            return saved;
        }
        iterator& operator+=(int n) {
            for (int i = 0; i < n; ++i) {
                ++(*this);
            }
            return *this;
        }
        bool operator==(const iterator& it) { return index == it.index; }
        bool operator!=(const iterator& it) { return !(*this == it); }
    };

    iterator begin() { return iterator(this, 0); }
    iterator end() { return iterator(this, size); }

    class const_iterator {
    private:
        const TinySet* set;
        int index;
    public:
        const_iterator(const TinySet* s, int ind) : set(s), index(ind) {}
        const int& operator*() const { return set->elements[index]; }
        const_iterator& operator++() {
            ++index;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator saved = *this;
            ++(*this);
            return saved;
        }
        const_iterator& operator+=(int n) {
            for (int i = 0; i < n; ++i) {
                ++(*this);
            }
            return *this;
        }
        bool operator==(const const_iterator& it) { return index == it.index; }
        bool operator!=(const const_iterator& it) { return !(*this == it); }
    };


    const_iterator cbegin() const { return const_iterator(this, 0); }
    const_iterator cend() const { return const_iterator(this, size); }
    bool empty() const { return !size; }
    bool full() const { return size == MAX_SIZE; }
    void print() const;
    int getSize() const { return size; }
private:
    int elements[MAX_SIZE];
    int size = 0;
private:
    void moveDown(int index);
    int getIndex(int) const;
};



bool TinySet::add(int x) {
    if (full() || contains(x))
        return false;
    elements[size] = x;
    moveDown(size);
    ++size;
    return true;
}

void TinySet::moveDown(int index) {
    int data = elements[index];
    while (index && elements[index - 1] > data) {
        elements[index] = elements[index - 1];
        --index;
    }
    elements[index] = data;
}

bool TinySet::contains(int x) const {
    if (getIndex(x) == -1) return false;
    return true;
}

int TinySet::getIndex(int x) const {
    int l = 0;
    int r = size - 1;
    int middle = l + (r - l) / 2;
    while (l <= r) {
        if (x == elements[middle])
            return middle;
        else if (x < elements[middle]) 
            r = middle - 1;
        else     
            l = middle + 1;
        middle = l + (r - l) / 2;
    }
    return -1;
}

bool TinySet::removeIfExists(int x) {
    int ind = getIndex(x);
    if (ind == -1) return false;
    for (int i = ind; i < size - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    --size;
    return true;
}

void TinySet::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << elements[i] << ' ';
    }
    std::cout << "\n";
}

int main() {
    TinySet set;
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    for (int i = 0; i < 8; ++i)
        set.add(arr[i]);
    for (TinySet::iterator it = set.begin(); it != set.end(); ++it) {
        *it *= 2;
    }
    for (int x : set)
        std::cout << x << ' ';
}
