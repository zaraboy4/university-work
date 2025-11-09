#include <iostream>

#define MAX_SIZE 256

class TinySet {
public:
    bool add(int);
    bool removeIfExists(int);
    bool contains(int) const;

    bool empty() const { return !size; }
    bool full() const { return size == MAX_SIZE; }

    void print() const;
    unsigned int getSize() const { return size; }
private:
    int elements[MAX_SIZE];
    unsigned int size = 0;
private:
    void moveDown(unsigned int index);
};

bool TinySet::add(int x) {
    if (full() || contains(x))
        return false;
    elements[size] = x;
    moveDown(size);
    ++size;
    return true;
}

void TinySet::moveDown(unsigned int index) {
    int data = elements[index];
    while (index && elements[index - 1] > data) {
        elements[index] = elements[index - 1];
        --index;
    }
    elements[index] = data;
}

bool TinySet::contains(int x) const {
    int l = 0;
    int r = size - 1;
    int middle = l + (r - l) / 2;
    while (l <= r) {
        if (x == elements[middle])  {
            std::cout << "index: " << middle << '\n';
            return true;
        }
        else if (x < elements[middle]) 
            r = middle - 1;
        else     
            l = middle + 1;
        middle = l + (r - l) / 2;
    }
    return false;
}

void TinySet::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << elements[i] << ' ';
    }
    std::cout << "\n";
}

int main() {
    TinySet set;
    int arr[] = { 7, 10, 23, 14, 3, -3, 5, 1 };
    for (int i = 0; i < 8; ++i)
        set.add(arr[i]);
    std::cout << set.contains(15);
    set.print();   
}
