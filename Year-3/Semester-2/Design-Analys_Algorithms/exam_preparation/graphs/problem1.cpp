#include "./Graph.hpp"
#include <fstream>

bool cycleDetectionUndirected(const Graph& graph, int v, int parent, std::vector<bool>& visited) {
    if (visited[v]) return true;
    visited[v] = true;
    for (int u : graph.g[v]) {
        if (parent != u && cycleDetectionUndirected(graph, u, v, visited)) {
            return true;
        }
    }
    return false;
}

bool cycleDetectionDirected(const Graph& graph, int v, std::vector<int>& visited) {
    visited[v] = 1; // mark it as in current branch
    for (int u : graph.g[v]) {
        if (visited[u] == 1) return true;
        if (visited[u] == 0 && cycleDetectionDirected(graph, u, visited)) {
            return true;
        }
    }
    visited[v] = 2;
    return false;
}

bool cycleDetection(const Graph& graph) {
    if (graph.directed == true) {
        std::vector<int> visited(graph.V, 0);
        for (int v = 0; v < graph.V; ++v) {
            if (visited[v] == 0) {
                if (cycleDetectionDirected(graph, v, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    else {
        std::vector<bool> visited(graph.V, false);
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v]) {
                if (cycleDetectionUndirected(graph, v, -1, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
}

int main() {
    // std::ifstream ifs("input_undirected.txt");
    // if (!ifs.is_open()) {
    //     std::cout << "invalid file name\n";
    //     return 1;
    // }
    // Graph graph(ifs, false);
    // graph.print();
    // std::cout <<  cycleDetection(graph);

    std::ifstream ifs2("input_directed.txt");
    if (!ifs2.is_open()) {
        std::cout << "invalid file name\n";
        return 2;
    }
    Graph graph2(ifs2, true);
    graph2.print();
    std::cout <<  cycleDetection(graph2);
    return 0;
}