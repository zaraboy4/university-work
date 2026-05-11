#include "./Graph.hpp"
#include <fstream>
#include <queue>

int shortestPathBFS(const Graph& graph, int v, int u) {
    std::vector<bool> visited(graph.V, false);
    std::queue<int> q;
    q.push(v);
    visited[v] = true;
    int cnt = 0;
    while (!q.empty()) {
        int curr = q.front();
        std::cout << curr + 1<< ' ';
        q.pop();
        //++cnt;
        for (int node : graph.g[curr]) {
            if (visited[node] == false) {
                //if (node == u) return cnt;
                //++cnt;
                q.push(node);
                visited[node] = true;
            }
        }
    }
    return cnt;
}

int main() {
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs);
    graph.print();
    std::cout << "Path length: " << shortestPathBFS(graph, 0, 4);
    return 0;
}