#include "./Graph.hpp"
#include <fstream>
#include <queue>

std::vector<int> shortestPathBFS(const Graph& graph, int v) {
    std::vector<int> level(graph.V, -1);
    std::queue<int> q;
    level[v] = 0;
    q.push(v);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int u : graph.g[curr]) {
            if (level[u] == -1) {
                level[u] = level[curr] + 1;
                q.push(u);
            }
        }
    }
    return level;
}

int main() {
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs);
    graph.print();
    int start = 0;
    std::vector<int> levels = shortestPathBFS(graph, start - 1);
    for (int v = 0; v < levels.size(); ++v) {
        std::cout << "from " << start << " to " << v + 1 << ": " << levels[v] << '\n';
    }
    return 0;
}
