#include <vector>
#include <iostream>
#include <set>

class Graph {
public:
    std::vector<std::vector<unsigned>> g;
    unsigned V;
public:
    Graph(const unsigned& vertexCount) : V(vertexCount) {
        g.resize(V);
    }
    void addEdge(const unsigned& u, const unsigned& v) {
        g[u].push_back(v);
    }
    void print() const {
        for (unsigned i = 0; i < V; ++i) {
            std::cout << i << ": ";
            for (const unsigned& u : g[i]) {
                std::cout << u << ' ';
            }
            std::cout << '\n';
        }
    }
};

bool containsCycleDFS(const Graph& graph, const unsigned& v, std::set<unsigned>& path, std::vector<bool>& visited) {
    visited[v] = true;
    path.insert(v);
    for (const unsigned& u : graph.g[v]) {
        if (path.find(u) != path.end()) {
            for (const unsigned& p : path) {
                std::cout << p << ' ';
            }
            std::cout << '\n';
            return true;
        }
        if (!visited[u] && containsCycleDFS(graph, u, path, visited)) {
            return true;
        }
    }
    path.erase(v);
    return false;; 
}

bool containsCycle(const Graph& graph, const unsigned& v) {
    std::vector<bool> visited(graph.V, false);
    std::set<unsigned> path;
    return containsCycleDFS(graph, v, path, visited);
}

int main() {
    Graph graph(6);
    graph.addEdge(0, 2);
    graph.addEdge(0, 4);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 0);
    graph.print();
    bool cycle = containsCycle(graph, 1);
    std::cout << "is cycle: " << cycle << '\n';
    return 0;
}