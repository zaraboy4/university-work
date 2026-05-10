#include "./Graph.hpp"
#include <fstream>
#include <queue>

bool colorBFS(const Graph& graph, int v, std::vector<int>& color) {
    std::queue<int> q;
    q.push(v);
    color[v] = 1;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int u : graph.g[curr]) {
            if (color[u] == -1) {
                color[u] = 1 - color[curr];
                q.push(u);
            }
            if (color[u] == color[curr]) 
                return false;
        }
    }
    return true;
}

bool checkBipartite(const Graph& graph) {
    std::vector<int> color(graph.V, -1);
    for (int v = 0; v < color.size(); ++v) {
        if (color[v] == -1 && !colorBFS(graph, v, color)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream ifs("input_notbipartite.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs);
    graph.print();
    std::cout << (checkBipartite(graph) ? "bipartite" : "not bipartite") << '\n';
    return 0;
}