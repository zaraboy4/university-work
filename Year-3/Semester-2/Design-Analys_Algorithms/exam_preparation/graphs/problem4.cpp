#include "./Graph.hpp"
#include <fstream>
#include <queue>

std::vector<int> topoSort(const Graph& graph) {
    std::vector<int> in_degree(graph.V, 0);
    for (int v = 0; v < graph.V; ++v) {
        for (int u : graph.g[v]) 
            ++in_degree[u];
    }

    std::queue<int> q;
    std::vector<int> topo;
    for (int v = 0; v < graph.V; ++v) {
        if (in_degree[v] == 0)
            q.push(v);
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        topo.push_back(curr);
        for (int u : graph.g[curr]) {
            --in_degree[u];
            if (in_degree[u] == 0) {
                q.push(u);
            }
        }
    }

    return topo;
}

int main() {
    std::ifstream ifs("input_directed.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs, true);
    graph.print();

    std::vector<int> topo = topoSort(graph);
    if (topo.size() < graph.V) {
        std::cout << "cycle detected\n";
    }
    for (int v : topo) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}