#ifndef _GRAPH_ADJANCENCY_LIST_IMPLEMENTATION_HPP
#define _GRAPH_ADJANCENCY_LIST_IMPLEMENTATION_HPP

#include <list>
#include <iostream>

template <class T>
class Graph {
private:
    std::list<std::list<T>> g;
private:
    std::list<T>* findVertexList(const T&);
public:
    bool addVertex(const T&);
    bool removeVertex(const T&);
    bool hasVertex(const T&) const;

    bool addEdge(const T&, const T&);
    bool removeEdge(const T&, const T&);
    bool hasEdge(const T&, const T&) const;

    std::list<T> getVertices() const;
    typename std::list<T>::iterator getSuccessors(const T&);

    void print() const;
};

template <class T>
std::list<T>* Graph<T>::findVertexList(const T& v) {
    for (typename std::list<std::list<T>>::iterator it = g.begin(); it != g.end(); ++it) {
        typename std::list<T>::iterator currListIt = (*it).begin();
        if (*currListIt == v) {
            return &*it;
        }
    }
    return nullptr;
}

template <class T>
bool Graph<T>::addVertex(const T& v) {
    // if (hasVertex(v)) {
    //     return false;
    // }
    std::list<T> newList;
    newList.push_back(v);
    g.push_back(newList);
    return true;
}

// template <class T>
// bool Graph<T>::removeVertex(const T& v) {
//     if (!hasVertex()) {
//         return false;
//     }
//     for (std::list<T>::iterator it = begin(); it != end(); ++it) {
//         if (*(*it).begin() == v) {
            
//         }
//     }
// }

// template <class T>
// bool Graph<T>::hasVertex(const T& v) const {
//     std::list<T> vertices = getVertices();
//     for (const T& u : vertices) {
//         if (u == v) {
//             return true;
//         }
//     }
//     return false;
// }

template <class T>
bool Graph<T>::addEdge(const T& u, const T& v) {
    std::list<T>* ptrVertexList = findVertexList(u);
    if (ptrVertexList == nullptr) {
        return false;
    }
    ptrVertexList->push_back(v);
    return true;
}

template <class T>
std::list<T> Graph<T>::getVertices() const {
    std::list<T> vertices;
    for (const std::list<T>& list : g) {
        vertices.push_back(list.front());
    }
    return vertices;
}

template <class T>
typename std::list<T>::iterator Graph<T>::getSuccessors(const T& v) {
    std::list<T>* ptrVertexList = findVertexList(v);
    if (ptrVertexList == nullptr) {
        return ptrVertexList->end();
    }
    typename std::list<T>::iterator it = ptrVertexList->begin();
    ++it;
    return it;
}

template <class T>
void Graph<T>::print() const {
    for (const std::list<T>& l : g) {
        for (const T& el : l) {
            std::cout << el << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

#endif