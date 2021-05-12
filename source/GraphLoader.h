//
// Created by sense on 05/05/2021.
//

#ifndef SOURCE_GRAPHLOADER_H
#define SOURCE_GRAPHLOADER_H

#include <list>
#include <tuple>
#include <fstream>

#include "Graph.h"

/*
template<class T>
void graphLoader(std::string node_file, std::string edge_file, Graph<T> &graph) {
    ifstream node_stream(node_file);

    if (node_stream.fail() || node_stream.eof() || node_stream.bad()){
        cout << "Failed to load node file" << endl;
        exit(1);
    }

    int size;
    char trash;

    node_stream >> size;

    for (int i = 0; i < size; i++){
        T value;
        int x, y;
        node_stream >> trash >> value >> trash >> x >> trash >> y >> trash;
        graph.addVertex(value); //TODO missing coords
    }

    ifstream edge_stream(edge_file);

    edge_stream >> size;

    for (int i = 0; i < size; i++){
        T id1, id2;
        edge_stream >> trash >> id1 >> trash >> id2 >> trash;
        graph.addEdge(id1, id2, 0, 0);
    }

}

*/
#endif //SOURCE_GRAPHLOADER_H
