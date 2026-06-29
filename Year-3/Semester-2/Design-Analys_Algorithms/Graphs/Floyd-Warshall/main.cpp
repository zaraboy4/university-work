#include "./WeightedGraph.hpp"
#include <fstream>

std::vector<std::vector<int>> floydWarshall(const WeightedGraph& graph) {
    int n = graph.V;
    std::vector<std::vector<int>> dist(n);
    for (int i = 0; i < n; ++i) {
        dist[i].resize(n, INT_MAX);
        dist[i][i] = 0;
    }
    for (const edge& e : graph.g) {
        dist[e.from][e.to] = e.w;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && 
                    dist[k][j] != INT_MAX && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

int main() {
    std::ifstream ifs("input_weighted.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    WeightedGraph graph(ifs, false);
    graph.print();
    auto dist = floydWarshall(graph);
    for (int i = 0; i < dist.size(); ++i) {
        for (int d : dist[i]) {
            std::cout << d << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}