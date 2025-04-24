#ifndef _GRAPH_IMPLEMENTATION_HEADER_INCLUDED_
#define _GRAPH_IMPLEMENTATION_HEADER_INCLUDED_

#include <iostream>
#include <fstream>

class Graph {
public:
    Graph() : g(nullptr), V(0) {}
    Graph(std::istream& is);
    ~Graph();
    void print() const;
public:
    int** g;
    int V;
private:
    void allocate();
};

Graph::Graph(std::istream& is) {
    is >> V;
    allocate();
    int f, s;
    while (is >> f) {
        is >> s;
        g[f - 1][s - 1] = 1;
        g[s - 1][f - 1] = 1;
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; ++i) {
        delete[] g[i];
    }
    delete[] g;
}

void Graph::print() const {
    std::cout << "Print Graph: " << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < V; ++j) {
            if (g[i][j] == 1)
                std::cout << j + 1 << ", ";
        }
        std::cout << std::endl;
    }
}

void Graph::allocate() {
    g = new int*[V];
    for (int i = 0; i < V; ++i) {
        g[i] = new int[V];
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j)
            g[i][j] = 0;
    }
}

#endif