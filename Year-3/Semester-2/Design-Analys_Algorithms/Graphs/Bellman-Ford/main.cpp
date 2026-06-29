#include "./WeightedGraph.hpp"
#include <fstream>

int main() {
    std::ifstream ifs("input_weighted.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    WeightedGraph graph(ifs, false);
    graph.print();
}