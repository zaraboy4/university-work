#ifndef _GRAPH_ADJANCENCY_LIST_IMPLEMENTATION_HPP
#define _GRAPH_ADJANCENCY_LIST_IMPLEMENTATION_HPP

#include <vector>

template <class T>
class Graph {
private:
    std::vector<std::vector<T>> g;
public:
    bool addVertex(const T&);
    bool removeVertex(const T&);
    bool hasVertex(const T&) const;

    bool addEdge(const T&, const T&);
    bool removeEdge(const T&, const T&);
    bool hasEdge(const T&, const T&) const;

    std::vector<T> getVertices() const;
    std::vector<T> getSuccessors(const T&) const;
};

template <class T>
bool Graph<T>::addVertex(const T& v) {
    if (hasVertex()) {
        return false;
    }
    std::vector<T> newList;
    newList.push_back(v);
    g.push_back(newList);
    return true;
}

template <class T>
bool Graph<T>::removeVertex(const T& v) {
    if (!hasVertex()) {
        return false;
    }
    for (std::vector<T>::iterator it = begin(); it != end(); ++it) {
        if (*(*it).begin() == v) {
            
        }
    }
}

template <class T>
bool Graph<T>::hasVertex(const T& v) const {
    std::vector<T> vertices = getVertices();
    for (const T& u : vertices) {
        if (u == v) {
            return true;
        }
    }
    return false;
}

template <class T>
std::vector<T> Graph<T>::getVertices() const {
    std::vector<T> vertices;
    for (const std::vector<T>& list : g) {
        vertices.push_back(list.front());
    }
    return vertices;
}

template <class T>
std::vector<T> Graph<T>::getSuccessors(const T& v) const {
    std::vector<T> successors;
    for (const std::vector<T>& list : g) {
        if (list.front() == v) {
            successors = list;
            successors.erase(successors.begin());
            break;
        }
    }
    return successors;
}

#endif