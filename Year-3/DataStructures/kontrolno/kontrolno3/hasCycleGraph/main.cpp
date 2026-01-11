#include <vector>
#include <iostream>
#include <fstream>
#include <set>

class Graph {
public:
    std::vector<std::vector<int>> g;
    unsigned V, E;
public:
    Graph(std::istream& in) {
        in >> V >> E;
        g.resize(V);
        unsigned u, v;
        for (unsigned i = 0; i < E; ++i) {
            in >> u >> v;
            addEdge(u, v);
        }
    }
    void addEdge(unsigned u, unsigned v) {
        g[u].push_back(v);
    }
    void print() const {
        for (unsigned i = 0; i < g.size(); ++i) {
            std::cout << i << ": ";
            for (unsigned node : g[i]) {
                std::cout << node << ' ';
            }
            std::cout << '\n';
        }
    }
};

bool containsCycleDFS(const Graph& graph, unsigned start, std::vector<bool>& visited, std::set<unsigned>& path) {
    visited[start] = true;
    path.insert(start);
    bool cycle = false;
    for (unsigned u : graph.g[start]) {
        if (path.find(u) != path.end()) {
            return true;
        }
        if (!visited[u]) {
            cycle = cycle || containsCycleDFS(graph, u, visited, path);
        }
    }
    path.erase(start);
    return cycle;
}

bool containsCycle(const Graph& graph) {
    std::vector<bool> visited(graph.V, false);
    std::set<unsigned> path;
    for (unsigned i = 0; i < graph.V; ++i) {
        if (!visited[i] && containsCycleDFS(graph, i, visited, path)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("input.txt");
    Graph graph(ifs);
    graph.print();
    std::cout << "cycle: " << containsCycle(graph) << '\n';
    return 0;
}