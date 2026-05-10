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
    void pushEdge(int u, int v);
};

Graph::Graph(std::istream& is) {
    is >> V;
    g.resize(V);
    int from, to;
    E = 0;
    while (is >> from >> to) {
        pushEdge(from, to);
        pushEdge(to, from);
        E++;
    }
}

void Graph::pushEdge(int u, int v) { // vertices from input file are 1-index based
    g[u - 1].push_back(v - 1);
}

void Graph::print() const {
    for (int v = 0; v < V; ++v) {
        std::cout << v + 1 << ": ";
        for (int u : g[v]) {
            std::cout << u + 1<< ' ';
        }
        std::cout << '\n';
    }
}