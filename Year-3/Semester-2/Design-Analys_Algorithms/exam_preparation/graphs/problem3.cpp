#include "./Graph.hpp"
#include <queue>
#include <fstream>

std::vector<int> shortestPathsBFS(const Graph& graph, int v) {
    std::vector<bool> visited(graph.V, false);
    std::vector<int> dist(graph.V, 0);
    std::queue<int> q;
    q.push(v);
    visited[v] = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int u : graph.g[curr]) {
            if (!visited[u]) {
                dist[u] = dist[curr] + 1;
                visited[u] = true;
                q.push(u);
            }
        }
    }
    return dist;
}

int main() {
    std::ifstream ifs("input_directed.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs, true);
    graph.print();
    std::vector<int> dist = shortestPathsBFS(graph, 0);
    for (int d : dist) std::cout << d << ' ';
    return 0;
}