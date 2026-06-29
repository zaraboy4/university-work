#include "./WeightedGraph.hpp"
#include <queue>
#include <fstream>

struct Compare {
    bool operator()(std::pair<int,int> p, std::pair<int,int> q) {
        return p.first >= q.first;
    }
};

std::vector<int> Dijkstra(const WeightedGraph& graph, int s) {
    std::priority_queue<std::pair<int,int>,
                        std::vector<std::pair<int,int>>,
                        Compare> pq;

    std::vector<int> dist(graph.V, INT_MAX);
    dist[s] = 0;
    pq.push({0,s});
    while (!pq.empty()) {
        std::pair<int,int> curr = pq.top();
        pq.pop();
        for (auto q : graph.g[curr.second]) {
            if (dist[curr.second] + q.second < dist[q.first]) {
                dist[q.first] = dist[curr.second] + q.second;
                pq.push({dist[q.first], q.first});
            }
        }
    }
    return dist;
}

int main() {
    std::ifstream ifs("input_weighted.txt");
    WeightedGraph graph(ifs, false);
    graph.print();
    std::vector<int> dist = Dijkstra(graph, 0);
    for (int d : dist) {
        std::cout << d << ' ';
    }
    std::cout << '\n';
    return 0;
}