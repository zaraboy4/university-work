#include "./Graph_2.hpp"

int main() {
    Graph g;
    for (int i = 0; i < 5; ++i) {
        g.addVertex(i + 1);
    }
    g.addEdge(2, 1);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(4, 3);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.print();
    return 0;
}