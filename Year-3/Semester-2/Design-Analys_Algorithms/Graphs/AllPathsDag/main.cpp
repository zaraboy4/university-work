#include <vector>
#include <queue>
#include <iostream>
using namespace std;

vector<int> topoSort(vector<vector<int>>& graph) {
    vector<int> in_degree(graph.size(), 0);
    for (int v = 0; v < graph.size(); ++v) {
        for (int u : graph[v]) {
            in_degree[u]++;
        }
    }
    queue<int> q;
    for (int v = 0; v < graph.size(); ++v) {
        if (!in_degree[v]) q.push(v);
    }
    vector<int> topo;
    while (!q.empty()) {
        int curr = q.front();
        topo.push_back(curr);
        q.pop();
        for (int u : graph[curr]) {
            in_degree[u]--;
            if (!in_degree[u]) q.push(u);
        }
    }

    return topo;
}
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    vector<vector<vector<int>>> paths(graph.size());
    vector<int> topo = topoSort(graph);
    paths[0].push_back({0});
    for (int t : topo) {
        for (int u : graph[t]) {
            vector<int> new_path;
            for (int i = 0; i < paths[t].size(); ++i) {
                new_path = paths[t][i];
                new_path.push_back(u);
                paths[u].push_back(new_path);
            }
        }
    }
    return paths[graph.size() - 1];
}

int main() {
    vector<vector<int>> graph = {{4,3,1},{3,2,4},{3},{4},{}};
    vector<vector<int>> paths = allPathsSourceTarget(graph);
    for (auto path : paths) {
        for (auto p : path) {
            cout << p << ' ';
        }
        cout << '\n';
    }
    return 0;
}