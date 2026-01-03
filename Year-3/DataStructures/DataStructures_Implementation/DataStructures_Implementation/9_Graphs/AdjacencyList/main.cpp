#include "./Graph.hpp"

int main() {
    Graph<int> g;
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
    std::list<int> vs = g.getVertices();
    for (const int& v : vs) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
    std::cout << g.hasVertex(2) << ' ';
    std::cout << g.hasVertex(6);
    return 0;
}