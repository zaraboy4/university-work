#include "./Graph.hpp"
#include <fstream>
#include <queue>

int shortestPathBFS(const Graph& graph, int v, int u) {
    if (v == u) return 0;
    std::vector<bool> visited(graph.V, false);
    std::queue<std::pair<int,int>> q;
    q.push({v,0});
    visited[v] = true;
    while (!q.empty()) {
        std::pair<int,int> p = q.front();
        //std::cout << '{' << p.first + 1 << ',' << p.second << "} ";
        q.pop();
        for (int node : graph.g[p.first]) {
            if (visited[node] == false) {
                if (node == u) return p.second + 1;
                q.push({node, p.second + 1});
                visited[node] = true;
            }
        }
    }
    return -1;
}

int main() {
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs);
    graph.print();
    for (int i = 0; i < graph.V; ++i) {
        std::cout << "Path length to " << i + 1<< ": " << shortestPathBFS(graph, 0, i) << '\n';
    }
    return 0;
}