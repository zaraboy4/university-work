#include <iostream>
#include "./StaticQueue.hpp"
 // add comment
int main() {
    try {
        StaticQueue<int> q;
        int arr[5] = { 1, 2, 3, 4, 5 };
        for (int i = 0; i < 5; ++i) {
            q.enqueue(arr[i]);
        }
        // q.print();
        StaticQueue<int> cp;
        cp.enqueue(10);
        cp.enqueue(20);
        // cp.print();
        cp = q;
        cp.enqueue(40);
        cp.enqueue(50);
        // cp.print();
    } catch (std::underflow_error& e) {
        std::cout << e.what();
    } catch (std::overflow_error& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "some error occured";
    }
    return 0;
}