#include "./Graph_2.hpp"

bool way(const int& u, const int& v, const Graph& graph, std::vector<int>& path) {
    path.push_back(u);
    if (u == v) {
        return true;
    }
    auto p = graph.getSuccessors(u);
    while (p.first != p.second) {
        if (!graph.member(*p.first, path) && way(*p.first, v, graph, path)) {
            return true;
        }
        ++p.first;
    }
    path.pop_back();
    return false;
}

bool wayDFS(const int& u, const int& v, const Graph& graph, std::vector<int>& path, std::vector<int>& visited) {
    path.push_back(u);
    visited.push_back(u);
    if (u == v) {
        return true;
    }
    auto p = graph.getSuccessors(u);
    while (p.first != p.second) {
        if (!graph.member(*p.first, visited) && wayDFS(*p.first, v, graph, path, visited)) {
            return true;
        }
        ++p.first;
    }
    path.pop_back();
    return false;
}

void allWays(const int& u, const int& v, const Graph& g, std::vector<int>& currPath, std::vector<std::vector<int>>& paths) {
    currPath.push_back(u);
    if (u == v) {
        paths.push_back(currPath);
    }
    else {
        auto p = g.getSuccessors(u);
        while (p.first != p.second) {
        if (!g.member(*p.first, currPath)) {
            allWays(*p.first, v, g, currPath, paths);
        }
        ++p.first;
    }
    }
    currPath.pop_back();
}

void test() {
    Graph g;
    for (int i = 0; i < 6; ++i) {
        g.addVertex(i + 1);
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            g.addEdge(i + 1, j + 1);
            g.addEdge(j + 1, i + 1);
        }
    }
    g.print();
    g.dfs(1);
    g.bfs(1);
    std::vector<int> currPath;
    std::vector<std::vector<int>> paths;
    allWays(1, 5, g, currPath, paths);
    for (const auto& path : paths) {
        for (const auto& p : path) {
            std::cout << p << ' ';
        }
        std::cout << '\n';
    }
    currPath.clear();
    std::cout << way(1, 6, g, currPath);
    currPath.clear();
    std::vector<int> visited;
    std::cout << wayDFS(1, 6, g, currPath, visited);
}

int main() {
    // test();
    // return 0;
    Graph g;
    for (int i = 0; i < 5; ++i) {
        g.addVertex(i + 1);
    }
    g.addEdge(2, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(4, 1);
    g.addEdge(2, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(4, 2);
    g.addEdge(4, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 4);
    g.addEdge(5, 3);
    g.addEdge(3, 5);
    g.print();
    g.dfs(2);
    g.bfs(2);
    std::vector<int> path, visited;
    std::cout << "is way: " << wayDFS(2, 5, g, path, visited) << '\n';
    for (const int& p : path) {
        std::cout << p << ' ';
    }
    return 0;
}