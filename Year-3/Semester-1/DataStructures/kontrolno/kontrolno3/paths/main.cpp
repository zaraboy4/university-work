#include <vector>
#include <iostream>

class Graph {
public:
    std::vector<std::vector<int>> g;
public:
    void addVertex(const int& v) {
        std::vector<int> list;
        list.push_back(v);
        g.push_back(list);
    }
    void addEdge(const int& u, const int& v) {
        std::vector<int>* ptrList = getList(u);
        ptrList->push_back(v);
        getList(v)->push_back(u);
    }
    std::vector<int> getSuccessors(const int& v) {
        std::vector<int> res = *getList(v);
        std::vector<int>::iterator it = res.begin();
        res.erase(it);
        return res;
    }
private:
    std::vector<int>* getList(const int& v) {
        for (std::vector<int>& list : g) {
            if (list.front() == v) {
                return &list;
            }
        }
        return nullptr;
    }
};

void print(const std::vector<int>& xs) {
    for (const int& x : xs) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

template <class T>
bool isMember(const T& el, const std::vector<T>& list) {
    for (const T& l : list) {
        if (l == el) {
            return true;
        }
    }
    return false;
}

bool isWayWithPath(Graph& g, std::vector<int>& path, const int& a, const int& b) {
    path.push_back(a);
    if (a == b) {
        return true;
    }
    std::vector<int> successors = g.getSuccessors(a);
    for (const int& v : successors) {
        if (!isMember(v, path) && isWayWithPath(g, path, v, b)) {
            return true;
        }
    }
    path.pop_back();
    return false;
}

bool isWayWithPathDFS(Graph& g, std::vector<int>& path, std::vector<int>& visited, const int& a, const int& b) {
    path.push_back(a);
    visited.push_back(a);
    if (a == b) {
        return true;
    }
    std::vector<int> successors = g.getSuccessors(a);
    for (const int& v : successors) {
        if (!isMember(v, visited) && isWayWithPathDFS(g, path, visited, v, b)) {
            return true;
        }
    }
    path.pop_back();
    return false;
}

void allWays(Graph& g, std::vector<int>& path, const int& a, const int& b) {
    path.push_back(a);
    if (a == b) {
        print(path);
    }
    else {
        std::vector<int> successors = g.getSuccessors(a);
        for (const int& v : successors) {
            if (!isMember(v, path)) {
                allWays(g, path, v, b);
            }
        }
    }
    path.pop_back();
}

int main() {
    Graph g;
    for (int i = 0; i < 6; ++i) {
        g.addVertex(i + 1);
    }
    g.addEdge(1, 2);
    g.addEdge(1, 6);
    g.addEdge(1, 3);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(5, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    std::vector<int> path;
    allWays(g, path, 1, 7);
    return 0;
}