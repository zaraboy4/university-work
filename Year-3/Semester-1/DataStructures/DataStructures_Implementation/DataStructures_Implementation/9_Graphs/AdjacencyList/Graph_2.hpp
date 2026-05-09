#include <vector>
#include <utility>
#include <iostream>
#include <queue>

class Graph {
private:
    std::vector<std::vector<int>> g;
    // bool oriented;
public:
    // Graph(bool _oriented = false) : oriented(_oriented) {}
    bool addVertex(const int& v) {
        if (hasVertex(v)) {
            return false;
        }
        std::vector<int> list;
        list.push_back(v);
        g.push_back(list);
        return true;
    }
    bool removeVertex(const int& v) {
        if (!hasVertex(v)) {
            return false;
        }
        std::vector<std::vector<int>>::iterator itLList = g.begin();
        while (itLList != g.end()) {
            std::vector<int>::iterator itCurrList = (*itLList).begin();
            if (*itCurrList == v) {
                itLList = g.erase(itLList);
            }
            else {
                while (itCurrList != (*itLList).end()) {
                    if (*itCurrList == v) {
                        itCurrList = (*itLList).erase(itCurrList);
                    }
                    else {
                        ++itCurrList;
                    }
                }
                ++itLList;
            }
        }
        return true;
    }
    bool hasVertex(const int& u) const {
        return findListVertex(u) != nullptr;
    }
    bool addEdge(const int& u, const int& v) {
        if (!hasVertex(u) || !hasVertex(v)) {
            return false;
        }
        findListVertex(u)->push_back(v);
        return true;
    }
    bool hasEdge(const int& u, const int& v) const {
        const std::vector<int>* ptrToList = findListVertex(u);
        if (!ptrToList) {
            return false;
        }
        for (const int& a : *ptrToList) {
            if (a == v) {
                return true;
            }
        }
        return false;
    }
    bool removeEdge(const int& u, const int& v) {
        std::vector<int>* ptrToList = findListVertex(u);
        if (!ptrToList) {
            return false;
        }
        std::vector<int>::iterator it = ptrToList->begin();
        while (it != ptrToList->end()) {
            if (*it == v) {
                it = ptrToList->erase(it);
                return true;
            }
            ++it;
        }
        return false;
    }

    const std::vector<int>* findListVertex(const int& v) const {
        for (std::vector<std::vector<int>>::const_iterator itLists = g.cbegin(); itLists != g.cend(); ++itLists) {
            std::vector<int>::const_iterator itCurrList = (*itLists).cbegin();
            if (*itCurrList == v) {
                return &*itLists;
            }
        }
        return nullptr;
    }

    std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> getSuccessors(const int& v) const {
        const std::vector<int>* ptrVertexList = findListVertex(v);
        std::vector<int>::const_iterator it_end = ptrVertexList->cend();
        if (!ptrVertexList) {
            return std::pair(it_end, it_end);
        }
        std::vector<int>::const_iterator it_begin = ptrVertexList->begin();
        ++it_begin;
        return std::pair(it_begin, it_end);
    }

    void print() const {
        for (const std::vector<int>& l : g) {
            for (const int& el : l) {
                std::cout << el << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    void printSuccessors(const int& v) const {
        std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> p = getSuccessors(v);
        if (p.first == p.second) {
            std::cout << "vertex has no successors\n";
        }
        else {
            while (p.first != p.second) {
                std::cout << *p.first << ' ';
                ++p.first;
            }
            std::cout << '\n';
        }
    }
    void dfs(const int& v) const {
        std::vector<int> visited;
        dfsRec(v, v, visited);
        std::cout << '\n';
    }
    void bfs(const int& v) const {
        std::queue<int> q;
        q.push(v);
        std::vector<int> visited;
        visited.push_back(v);
        while (!q.empty()) {
            int el = q.front();
            q.pop();
            // std::cout << el << ' ';
            auto p = getSuccessors(el);
            while (p.first != p.second) {
                if (!member(*p.first, visited)) {
                    std::cout << '(' << el << ", " << *p.first << ')';
                    q.push(*p.first);
                    visited.push_back(*p.first);
                }
                ++p.first;
            }
        }
        std::cout << '\n';
    }
    bool member(const int& el, std::vector<int>& xs) const {
        for (const int& x : xs) {
            if (x == el) return true;
        }
        return false;
    }
private:
    std::vector<int>* findListVertex(const int& v) {
        for (std::vector<std::vector<int>>::iterator itLists = g.begin(); itLists != g.end(); ++itLists) {
            std::vector<int>::iterator itCurrList = (*itLists).begin();
            if (*itCurrList == v) {
                return &*itLists;
            }
        }
        return nullptr;
    }

    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> getSuccessors(const int& v) {
        std::vector<int>* ptrVertexList = findListVertex(v);
        std::vector<int>::iterator it_end = ptrVertexList->end();
        if (!ptrVertexList) {
            return std::pair(it_end, it_end);
        }
        std::vector<int>::iterator it_begin = ptrVertexList->begin();
        ++it_begin;
        return std::pair(it_begin, it_end);
    }
  
    void dfsRec(const int& v, const int& parent, std::vector<int>& visited) const {
        if (!visited.empty()) {
            std::cout << '(' << parent << ", " << v << ")";
        }
        visited.push_back(v);
        std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> p = getSuccessors(v);
        while (p.first != p.second) {
            if (!member(*p.first, visited)) {
                dfsRec(*p.first, v, visited);
            }
            ++p.first;
        }
    }
};