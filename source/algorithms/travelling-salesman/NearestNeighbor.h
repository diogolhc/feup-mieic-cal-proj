#ifndef SOURCE_NEARESTNEIGHBOR_H
#define SOURCE_NEARESTNEIGHBOR_H

#include "../../Graph.h"
#include "../../agents/Truck.h"

#include <vector>

class NearestNeighbor {

    std::vector<Vertex *> running_path;
    Truck * truck;
    Vertex * s;
    Graph * graph;

public:
    void initialize(Graph * graph, size_t origin_id, Truck * truck);
    std::vector<Vertex *> run(); //returns visiting order of the vertex
};


#endif //SOURCE_NEARESTNEIGHBOR_H
