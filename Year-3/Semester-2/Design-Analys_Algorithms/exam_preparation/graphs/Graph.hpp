#include <vector>
#include <iostream>

class Graph {
public:
    std::vector<std::vector<int>> g;
    int V;
    bool directed;
public:
    Graph(std::istream&, bool directed);
    void addEdge(int u, int v);
    void print() const;
};

Graph::Graph(std::istream& is, bool directed = false) : directed(directed) {
    is >> V;
    g.resize(V);
    int u, v;
    while (is >> u >> v) {
        addEdge(u, v);
        if (!directed) addEdge(v, u);
    }
}

void Graph::addEdge(int u, int v) {
    g[u].push_back(v);
}

void Graph::print() const {
    for (int v = 0; v < V; ++v) {
        std::cout << v << ": ";
        for (int u : g[v]) {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }
}