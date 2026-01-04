#include <vector>
#include <iostream>
#include <fstream>

class Graph {
private:
    std::vector<std::vector<int>> g;
public:
    void createGraph(std::istream& in) {
        int numVertices, numEdges, u, v;
        in >> numVertices >> numEdges;
        for (int i = 0; i < numVertices; ++i) {
            in >> v;
            addVertex(v);
        }
        for (int i = 0; i < numEdges; ++i) {
            in >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
    }

    void addVertex(const int& v) {
        std::vector<int> newList;
        newList.push_back(v);
        g.push_back(newList);
    }

    void addEdge(const int& u, const int& v) {
        for (std::vector<int>& list : g) {
            if (u == list.front()) {
                list.push_back(v);
                break;
            }
        }
    }

    void print() const {
        for (const std::vector<int>& list : g) {
            for (const int& l : list) {
                std::cout << l << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    std::vector<int> getSuccessors(const int& v) const {
        std::vector<int> res;
        for (const std::vector<int>& list : g) {
            if (list.front() == v) {
                res = list;
                break;
            }
        }
        if (res.empty()) {
            return res;
        }
        res.erase(res.begin());
        return res;
    }

    std::vector<int> getVertices() const {
        std::vector<int> res;
        for (const std::vector<int>& list : g) {
            res.push_back(list.front());
        }
        return res;
    }

    void dfs(const int& v) const {
        std::vector<int> visited;
        dfsRec(v, visited);
    }

    void dfsRec(const int& v, std::vector<int>& visited) const {
        // std::cout << v << ' ';
        visited.push_back(v);
        std::vector<int> successors = getSuccessors(v);
        for (const int& u : successors) {
            if (!isMember(u, visited)) {
                dfsRec(u, visited);
            }
        }
    }

    bool isMember(const int& v, std::vector<int>& list) const {
        for (const int& l : list) {
            if (l == v) {
                return true;
            }
        }
        return false;
    }

    unsigned getCountConnectedComponents() const {
        unsigned int count = 0;
        std::vector<int> visited;
        std::vector<int> vertices = getVertices();
        for (const int& v : vertices) {
            if (!isMember(v, visited)) {
                dfsRec(v, visited);
                ++count;
            }
        }
        return count;
    }
};

int main() {
    std::ifstream ifs("input.txt");
    Graph g;
    g.createGraph(ifs);
    g.print();
    // std::cout << "dfs: ";
    // g.dfs(1);
    std::cout << "cnt cnntd cmpnts: " << g.getCountConnectedComponents() << '\n';
    return 0;
}

