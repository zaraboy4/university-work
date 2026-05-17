#include <iostream>
#include <vector>
#include <queue>

void push_edge(std::vector<std::vector<int>>& graph, int v, int u) {
    graph[v - 1].push_back(u - 1);
}

std::vector<int> topoSort(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> in_degree(n, 0);
    for (int v = 0; v < n; ++v) {
        for (int u : graph[v]) {
            in_degree[u]++; 
        }
    }
    std::queue<int> q;
    for (int v = 0; v < n; ++v) {
        if (in_degree[v] == 0) {
            q.push(v);
        }
    }
    std::vector<int> topo;
    while (!q.empty()) {
        int curr = q.front();
        topo.push_back(curr);
        q.pop();
        for (int u : graph[curr]) {
            in_degree[u]--;
            if (in_degree[u] == 0) {
                q.push(u);
            }
        }
    }
    return topo;
}

int countPathsDAG(const std::vector<std::vector<int>>& graph, int s, int t) {
    --s; --t;
    int n = graph.size();
    std::vector<int> topo = topoSort(graph);
    std::vector<int> dp(n, 0);
    dp[s] = 1;
    for (int v : topo) {
        for (int u : graph[v]) {
            dp[u] += dp[v];
        }
    }

    std::cout << "dp: ";
    for (int i = 0; i < n; ++i) {
        std::cout << dp[i] << ' ';
    }
    std::cout << '\n';
    return dp[t];
}

int main() {
    std::vector<std::vector<int>> graph(6);
    push_edge(graph, 4, 2);
    push_edge(graph, 4, 3);
    push_edge(graph, 4, 5);
    push_edge(graph, 2, 3);
    push_edge(graph, 3, 1);
    push_edge(graph, 5, 1);
    push_edge(graph, 1, 6);
    push_edge(graph, 3, 6);
    push_edge(graph, 2, 6);
    std::vector<int> topo = topoSort(graph);
    std::cout << "topo sorted: ";
    for (int v : topo) {
        std::cout << v + 1 << ' '; 
    }
    std::cout << '\n';
    int res = countPathsDAG(graph, 6, 5);
    return 0;
}