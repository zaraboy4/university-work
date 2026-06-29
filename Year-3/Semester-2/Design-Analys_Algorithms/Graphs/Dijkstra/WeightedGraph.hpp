#include <vector>
#include <iostream>

class WeightedGraph {
public:
    std::vector<std::vector<std::pair<int,int>>> g;
    int V;
    bool directed;
public:
    WeightedGraph(std::istream&, bool directed);
    void addEdge(int u, int v, int w);
    void print() const;
};

WeightedGraph::WeightedGraph(std::istream& is, bool directed = false) : directed(directed) {
    is >> V;
    g.resize(V);
    int u, v, w;
    while (is >> u >> v >> w) {
        addEdge(u, v, w);
        if (!directed) addEdge(v, u, w);
    }
}

void WeightedGraph::addEdge(int u, int v, int w) {
    g[u].push_back({v, w});
}

void WeightedGraph::print() const {
    for (int v = 0; v < V; ++v) {
        std::cout << v << ": ";
        for (auto u : g[v]) {
            std::cout << '{' << u.first << ',' << u.second << '}';
        }
        std::cout << '\n';
    }
}