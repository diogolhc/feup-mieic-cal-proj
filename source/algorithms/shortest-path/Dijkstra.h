//
// Created by sense on 12/05/2021.
//

#ifndef SOURCE_DIJKSTRA_H
#define SOURCE_DIJKSTRA_H

#include "../../Graph.h"

#include <unordered_map>

class Dijkstra {
    Vertex * s;
    Graph * graph;
    unordered_map<Vertex *, size_t> dist;
    unordered_map<Vertex *, Vertex *> path;
public:
    void initialize(Graph * graph, int origin_id);
    void run();
    unordered_map<Vertex *, Vertex *> getPath() const;
};


#endif //SOURCE_DIJKSTRA_H
