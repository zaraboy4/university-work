#include <vector>
#include <iostream>

struct edge {
    int from;
    int to;
    int w;
};

class WeightedGraph {
public:
    std::vector<edge> g;
    int V, E;
    bool directed;
public:
    WeightedGraph(std::istream&, bool directed);
    void addEdge(int u, int v, int w);
    void print() const;
};

WeightedGraph::WeightedGraph(std::istream& is, bool directed = false) : directed(directed) {
    is >> V;
    int u, v, w;
    while (is >> u >> v >> w) {
        addEdge(u, v, w);
        if (!directed) addEdge(v, u, w);
    }
    E = g.size() / 2;
}

void WeightedGraph::addEdge(int u, int v, int w) {
    g.push_back({u, v, w});
}

void WeightedGraph::print() const {
    for (auto edge : g) {
        printf("{%d,%d,%d}\n", edge.from, edge.to, edge.w);
    }
}