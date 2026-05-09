#include <iostream>
#include <vector>
#include <fstream>

class Graph {
public:
    int V, E;
    bool directed;
    std::vector<std::vector<int>> g;
public:
    Graph(std::istream& is, bool directed = false) : directed(directed){
        is >> V >> E;
        g.resize(V);
        int from, to;
        for (int i = 0; i < E; ++i) {
            is >> from >> to;
            pushEdge(from, to);
            if (directed == false) {
                pushEdge(to, from);
            }
        }
    }

    void print() {
        for (int v = 0; v < V; ++v) {
            std::cout << v << ": ";
            for (auto& u : g[v]) {
                std::cout << u << ' ';
            }
            std::cout << '\n';
        }
    }
private:
    void pushEdge(int u, int v) {
        g[u].push_back(v);
    }
};

bool cycleDFS_directed(Graph& graph, int v, std::vector<int>& state) {
    state[v] = 1;
    for (int u : graph.g[v]) {
        if (state[u] == 1) return true;
        if (state[u] == 0 && cycleDFS_directed(graph, u, state)) return true;
    }
    state[v] = 2;
    return false;
}

bool cycleDetectionDFS_directed(Graph& graph) {
    std::vector<int> state(graph.V, 0);
    for (int v = 0; v < graph.V; ++v) {
        if (state[v] == 0 && cycleDFS_directed(graph, v, state)) {
            return true;
        }
    }
    return false;
}

bool cycleDFS_undirected(Graph& graph, int v, std::vector<int>& state) {
    state[v] = 2;
    for (int u : graph.g[v]) {
        if (state[u] == 2) return true;
        if (state[u] == 0 && cycleDFS_undirected(graph, u, state)) {
            return true;
        }
    }
    return false;
}

bool cycleDetectionDFS_undirected(Graph& graph) {
    std::vector<int> state(graph.V, 0);
    for (int v = 0; v < graph.V; ++v) {
        if (state[v] == 0 && cycleDFS_undirected(graph, v, state)) {
            return true;
        }
    }
    return false;
}

bool cycleDetectionDFS(Graph& graph) {
    if (graph.directed) {
        return cycleDetectionDFS_directed(graph);
    }
    else {
        return cycleDetectionDFS_undirected(graph);
    }
}

int main() {
    std::ifstream ifs("input_undirected.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 0;
    }

    Graph graph(ifs, false);
    graph.print();
    std::cout << (cycleDetectionDFS(graph) ? "cycle" : "not cycle") << '\n';
    return 0;
}