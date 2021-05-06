#include <iostream>

#include "Graph.h"
#include "GraphLoader.h"

using namespace std;

int main() {

    string node_file = "../../maps/Mapas-20210505/GridGraphs/4x4/nodes.txt";
    string edge_file = "../../maps/Mapas-20210505/GridGraphs/4x4/edges.txt";
    Graph<int> graph;

    graphLoader<int>(node_file, edge_file, graph);

    std::cout << "Hello, World!" << std::endl;

    return 0;
}

