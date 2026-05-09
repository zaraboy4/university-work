#include <vector>
#include <iostream>
#include <fstream>

class Graph {
public:
    std::vector<std::vector<int>> g;
    int V, E;
public:
    Graph(std::istream& is) {
        is >> V >> E;
        g.resize(V);
        int u, v;
        for (int i = 0; i < E; ++i) {
            is >> u >> v;
            addEdge(u, v);
        }
    }

    void addEdge(const int& u, const int& v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
};

void dfs(const Graph& graph, const int& v, std::vector<int>& connectedComponent, std::vector<bool>& visited) {
    connectedComponent.push_back(v);
    visited[v] = 1;
    for (const int& u : graph.g[v]) {
        if (!visited[u]) {
            dfs(graph, u, connectedComponent, visited);
        }
    }
}

double getAverageList(const std::vector<int>& list) {
    int sum = 0;
    for (const int& l : list) {
        sum += l;
    }
    return sum * 1.0 / list.size();
}

double sumOfAverageInConnectedComponents(const Graph& graph) {
    double sum = 0;
    std::vector<int> connectedComponent;
    std::vector<bool> visited(graph.V, false);
    for (int i = 0; i < graph.V; ++i) {
        if (!visited[i]) {
            dfs(graph, i, connectedComponent, visited);
            sum += getAverageList(connectedComponent);
            connectedComponent.clear();
        }
    }
    return sum;
}

int main() {
    std::ifstream ifs("input2.txt");
    Graph g(ifs);
    std::cout << "res: " << sumOfAverageInConnectedComponents(g) << '\n';
    return 0;
}