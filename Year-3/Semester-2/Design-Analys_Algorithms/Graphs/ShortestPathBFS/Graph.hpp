#include <vector>
#include <iostream>

class Graph {
public:
    int V, E;
    std::vector<std::vector<int>> g;
public:
    Graph(std::istream& is);
    void print() const;
private:
    void pushEdge(int from, int to);
};

Graph::Graph(std::istream& is) {
    is >> V;
    g.resize(V);
    E = 0;
    int from, to;
    while (is >> from >> to) {
        pushEdge(from, to);
        pushEdge(to, from);
        ++E;
    }
}

void Graph::pushEdge(int from, int to) {
    g[from - 1].push_back(to - 1);
}

void Graph::print() const {
    for (int v = 0; v < V; ++v) {
        std::cout << v + 1 << ": ";
        for (int u : g[v]) {
            std::cout << u + 1 << ' ';
        }
        std::cout << '\n';
    }
}