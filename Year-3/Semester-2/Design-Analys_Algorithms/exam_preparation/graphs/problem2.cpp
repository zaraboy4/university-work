#include "./Graph.hpp"
#include <fstream>
#include <queue>


bool twoColouringBFS(const Graph& graph, int v, std::vector<int>& colours) {
    std::queue<int> q;
    q.push(v);
    colours[v] = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int u : graph.g[curr]) {
            if (colours[u] == colours[curr]) {
                return false;
            }
            if (colours[u] == -1) {
                colours[u] = (colours[curr] + 1) % 2;
                q.push(u);
            }
        }
    }
    return true;
}

bool twoColouring(const Graph& graph) {
    std::vector<int> colours(graph.V, -1);
    for (int v = 0; v < graph.V; ++v) {
        if (colours[v] == -1 && !twoColouringBFS(graph, v, colours)) {
            for (int col : colours) {
                std::cout << col << ' ';
            }
            std::cout << '\n';
            return false;
        }
    }
    for (int col : colours) {
        std::cout << col << ' ';
    }
    std::cout << '\n';
    return true;
}

int main() {
    std::ifstream ifs("input_undirected.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    Graph graph(ifs, true);
    graph.print();
    bool res = twoColouring(graph);
    std::cout << "is 2-coloring: " << res << '\n';
    return 0;
}