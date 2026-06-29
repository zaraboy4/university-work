#include "./WeightedGraph.hpp"
#include <fstream>

std::vector<int> bellmanFord(const WeightedGraph& graph, int s) {
    std::vector<int> dist(graph.V, INT_MAX);
    dist[s] = 0;
    for (int i = 0; i < graph.V - 1; ++i) {
        for (const edge& e : graph.g) {
            if (dist[e.from] + e.w < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.w;
            }
        }
    }

    for (const edge& e : graph.g) {
        if (dist[e.to] != INT_MAX && dist[e.from] + e.w < dist[e.to]) {
            std::cout << "detected negative cycle\n";
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
    WeightedGraph graph(ifs, true);
    graph.print();

    std::vector<int> dist = bellmanFord(graph, 0);
    for (int d : dist) {
        std::cout << d << ' ';
    }
    std::cout << '\n';
}