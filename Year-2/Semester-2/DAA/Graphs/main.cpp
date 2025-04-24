#include "Graph.hpp"

int countCycles(const Graph& gr) {
    int cnt = 0;
    for (int i = 0; i < gr.V; ++i) {
        for (int j = i + 1; j < gr.V; ++j) {
            for (int k = j + 1; k < gr.V; ++k) {
                if (gr.g[i][j] == 1 && gr.g[j][k] == 1 && gr.g[k][i] == 1) ++cnt;
            }
        }
    }
    // for (int i = 0; i < gr.V; ++i) {
    //     for (int j = 0; j < gr.V; ++j) {
    //         for (int k = 0; k < gr.V; ++k) {
    //             if (gr.g[i][j] == 1 && gr.g[j][k] == 1 && gr.g[k][i] == 1) ++cnt;
    //         }
    //     }
    // }
    // cnt /= 6;
    return cnt;
}

int main() {
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cout << "wrong file name";
        return 0;
    }
    Graph g(ifs);
    g.print();
    std::cout << "Count 3-length cycles: " << countCycles(g);
    return 0;
}