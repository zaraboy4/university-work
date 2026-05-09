#include <iostream>
#include <vector>
#include <fstream>

class Graph {
public:
    int V, E;
    std::vector<std::vector<int>> g;
public:
    Graph(std::istream& is) {
        is >> V >> E;
        g.resize(V);
        int from, to;
        for (int i = 0; i < E; ++i) {
            is >> from >> to;
            pushEdge(from, to);
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

bool cycleDFS(Graph& graph, int v, std::vector<int>& state) {
    state[v] = 1;
    for (int u : graph.g[v]) {
        if (state[u] == 1) return true;
        if (state[u] == 0 && cycleDFS(graph, u, state)) return true;
    }
    state[v] = 2;
    return false;
}

bool cycleDetectionDFS(Graph& graph) {
    std::vector<int> state(graph.V, 0);
    for (int v = 0; v < graph.V; ++v) {
        if (state[v] == 0 && cycleDFS(graph, v, state)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 0;
    }

    Graph graph(ifs);
    graph.print();
    std::cout << (cycleDetectionDFS(graph) ? "cycle" : "not cycle") << '\n';
    return 0;
}