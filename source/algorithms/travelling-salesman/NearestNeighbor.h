//
// Created by sense on 12/05/2021.
//

#ifndef SOURCE_NEARESTNEIGHBOR_H
#define SOURCE_NEARESTNEIGHBOR_H

#include "../../Graph.h"

#include <vector>

class NearestNeighbor {

    std::vector<Vertex *> running_path;
    std::vector<int> application_center_ids;
    Vertex * s;
    Graph * graph;

public:
    void initialize(Graph * graph, int origin_id, const std::vector<int>& application_center_ids);
    std::vector<Vertex *> run(); //returns visiting order of the vertex
};


#endif //SOURCE_NEARESTNEIGHBOR_H
